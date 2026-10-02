#!/usr/bin/env python3
"""
pla2dig.py  --  .pla  ->  espresso  ->  Digital (.dig) circuit, driven by the lab Template

The university grader only cares about the In/Out pins of the template
(label + bit width).  So the template is the contract:

    gen   : read Template-0N.dig, keep its In/Out pins byte-for-byte, throw the
            rest away, minimise the .pla with espresso and wire a two-level
            SOP circuit to those pins.  A Testcase built from the .pla is
            embedded and Digital's CLI test is run on the result.
    check : compare any .dig against a template (same pins?) and run its tests.

    pla2dig.py gen   labs/lab03_encoder.pla --template ../../Labs/Lab03/Template-03.dig -o ../../Labs/Lab03/out/03.dig
    pla2dig.py check ../../Labs/Lab03/out/03.dig      --template ../../Labs/Lab03/Template-03.dig

PLA signal names follow the template pins:
    1-bit pin  A            ->  A
    bus  pin   In (4 bit)   ->  In3 In2 In1 In0      (or In[3] ...)
No .ilb/.ob at all -> positional, template pin order, MSB first.
Short names: put "#map Selector=S1,S0" / "#map Output=O3,O2,O1,O0" in the .pla
(or pass --map ...).  The circuit's tunnels are named after the PLA signals.
"""
import argparse
import itertools
import os
import re
import shutil
import subprocess
import sys
import tempfile
from typing import Dict, List, Optional, Tuple

SIZE = 20  # Digital grid unit


# --------------------------------------------------------------------------- #
#  PLA parsing / espresso
# --------------------------------------------------------------------------- #
class Pla:
    def __init__(self):
        self.ni = 0
        self.no = 0
        self.ilb: List[str] = []
        self.ob: List[str] = []
        self.type = "fd"
        self.cubes: List[Tuple[str, str]] = []  # (input part, output part)
        self.maps: List[str] = []               # "#map Selector=S1,S0" lines


def parse_pla(text: str) -> Pla:
    p = Pla()
    for raw in text.splitlines():
        m = re.match(r"\s*#\s*map\s+(\S+)", raw)
        if m:
            p.maps.append(m.group(1))
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        if line.startswith("."):
            tok = line.split()
            key = tok[0]
            if key == ".i":
                p.ni = int(tok[1])
            elif key == ".o":
                p.no = int(tok[1])
            elif key == ".ilb":
                p.ilb = tok[1:]
            elif key == ".ob":
                p.ob = tok[1:]
            elif key == ".type":
                p.type = tok[1]
            elif key in (".e", ".end"):
                break
            # .p and anything else are ignored
            continue
        tok = line.split()
        if len(tok) == 2:
            inp, out = tok
        else:  # allow "101 | 01" or "1 0 1 0 1"
            s = line.replace("|", " ").replace(" ", "")
            inp, out = s[: p.ni], s[p.ni:]
        if len(inp) != p.ni or len(out) != p.no:
            raise ValueError("bad cube width: %r" % raw)
        p.cubes.append((inp, out))
    if p.ilb and len(p.ilb) != p.ni:
        raise ValueError(".ilb has %d names but .i is %d" % (len(p.ilb), p.ni))
    if p.ob and len(p.ob) != p.no:
        raise ValueError(".ob has %d names but .o is %d" % (len(p.ob), p.no))
    return p


def run_espresso(pla_path: str, espresso: str, extra: List[str]) -> str:
    exe = shutil.which(espresso) or espresso
    if not os.path.exists(exe):
        sys.exit("espresso not found: %s  (use --espresso PATH or --no-espresso)" % espresso)
    r = subprocess.run([exe] + extra + [pla_path], capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("espresso failed:\n" + r.stderr)
    return r.stdout


# --------------------------------------------------------------------------- #
#  Template (.dig) parsing -- regex based, the pin XML is kept verbatim
# --------------------------------------------------------------------------- #
ELEM_RE = re.compile(r"[ \t]*<visualElement>.*?</visualElement>\n?", re.S)
WIRES_RE = re.compile(r"<wires>(.*?)</wires>", re.S)


class Pin:
    def __init__(self, kind: str, label: str, bits: int, x: int, y: int, rot: int, xml: str):
        self.kind, self.label, self.bits, self.x, self.y, self.rot, self.xml = \
            kind, label, bits, x, y, rot, xml

    def __repr__(self):
        return "%s[%d]" % (self.label, self.bits)

    def xml_at(self, x: int, y: int) -> str:
        """The verbatim pin block moved to (x, y), rotation cleared (label/bits untouched)."""
        b = re.sub(r'<pos x="-?\d+" y="-?\d+"\s*/>', '<pos x="%d" y="%d"/>' % (x, y), self.xml)
        b = re.sub(r'\s*<entry>\s*<string>rotation</string>\s*<rotation[^>]*/>\s*</entry>', "", b)
        return b

    def free_dir(self) -> Tuple[int, int]:
        """Unit vector pointing away from the pin body (where a wire can attach)."""
        d = [(1, 0), (0, -1), (-1, 0), (0, 1)][self.rot % 4]   # In: rotation 0 -> +x
        return d if self.kind == "In" else (-d[0], -d[1])


def _attr(block: str, name: str, tag: str) -> Optional[str]:
    m = re.search(r"<string>%s</string>\s*<%s>(.*?)</%s>" % (re.escape(name), tag, tag), block, re.S)
    return m.group(1) if m else None


def _rotation(block: str) -> Tuple[int, Optional[str]]:
    m = re.search(r'<rotation rotation="(\d)"\s*/>', block)
    if m:
        return int(m.group(1)), None
    m = re.search(r'<rotation reference="([^"]*)"\s*/>', block)
    if m:
        return 0, m.group(1)
    return 0, None


class Template:
    def __init__(self, path: str):
        self.path = path
        self.text = open(path).read()
        self.blocks: List[str] = ELEM_RE.findall(self.text)
        self.pins: List[Pin] = []
        self.others: List[str] = []
        for b in self.blocks:
            m = re.search(r"<elementName>(.*?)</elementName>", b)
            kind = m.group(1) if m else ""
            if kind not in ("In", "Out"):
                self.others.append(b)
                continue
            label = _attr(b, "Label", "string") or ""
            bits = int(_attr(b, "Bits", "int") or 1)
            pm = re.search(r'<pos x="(-?\d+)" y="(-?\d+)"\s*/>', b)
            x, y = int(pm.group(1)), int(pm.group(2))
            rot, ref = _rotation(b)
            if ref:  # xstream wrote "same as element N": resolve it, indices change when we drop elements
                rot = self._resolve_rotation(ref)
                b = re.sub(r'<rotation reference="[^"]*"\s*/>', '<rotation rotation="%d"/>' % rot, b)
            if 'reference="' in b:
                sys.exit("%s: pin %s uses an XML reference I cannot resolve:\n%s" % (path, label, b))
            self.pins.append(Pin(kind, label, bits, x, y, rot, b))
        wm = WIRES_RE.search(self.text)
        self.wires_xml = wm.group(1) if wm else ""

    def _resolve_rotation(self, ref: str) -> int:
        m = re.search(r"visualElement\[(\d+)\]", ref)
        idx = int(m.group(1)) - 1 if m else 0
        rot, _ = _rotation(self.blocks[idx])
        return rot

    @property
    def inputs(self) -> List[Pin]:
        return [p for p in self.pins if p.kind == "In"]

    @property
    def outputs(self) -> List[Pin]:
        return [p for p in self.pins if p.kind == "Out"]

    def interface(self) -> str:
        return "%s -> %s" % (" ".join("%s[%d]" % (p.label, p.bits) for p in self.inputs),
                             " ".join("%s[%d]" % (p.label, p.bits) for p in self.outputs))

    def signature(self):
        return (tuple(sorted((p.label, p.bits) for p in self.inputs)),
                tuple(sorted((p.label, p.bits) for p in self.outputs)))

    def bbox(self, include_others: bool) -> Tuple[int, int, int, int]:
        xs, ys = [], []
        blocks = self.blocks if include_others else [p.xml for p in self.pins]
        for b in blocks:
            for mx, my in re.findall(r'<pos x="(-?\d+)" y="(-?\d+)"\s*/>', b):
                xs.append(int(mx))
                ys.append(int(my))
        if include_others:
            for mx, my in re.findall(r'<p[12] x="(-?\d+)" y="(-?\d+)"\s*/>', self.wires_xml):
                xs.append(int(mx))
                ys.append(int(my))
        return min(xs), min(ys), max(xs), max(ys)


# --------------------------------------------------------------------------- #
#  .dig XML builder
# --------------------------------------------------------------------------- #
def xml_esc(s: str) -> str:
    return (s.replace("&", "&amp;").replace("<", "&lt;")
             .replace(">", "&gt;").replace('"', "&quot;"))


class Dig:
    def __init__(self):
        self.elems: List[str] = []
        self.wires: List[Tuple[int, int, int, int]] = []
        self.raw_wires = ""

    def add_raw(self, block: str):
        self.elems.append(block if block.endswith("\n") else block + "\n")

    def add(self, name: str, x: int, y: int, attrs: Optional[List[Tuple[str, str]]] = None):
        """attrs: list of (key, rawXmlValue)"""
        if attrs:
            body = "".join(
                "        <entry>\n          <string>%s</string>\n          %s\n        </entry>\n"
                % (xml_esc(k), v) for k, v in attrs)
            body = "      <elementAttributes>\n%s      </elementAttributes>\n" % body
        else:
            body = "      <elementAttributes/>\n"
        self.elems.append(
            "    <visualElement>\n      <elementName>%s</elementName>\n%s"
            "      <pos x=\"%d\" y=\"%d\"/>\n    </visualElement>\n" % (name, body, x, y))

    def wire(self, x1: int, y1: int, x2: int, y2: int):
        if (x1, y1) != (x2, y2):
            self.wires.append((x1, y1, x2, y2))

    # element shortcuts -----------------------------------------------------
    def tunnel(self, net: str, x: int, y: int, rot: int = 0):
        a = []
        if rot:  # 2 = label drawn to the left of the pin
            a.append(("rotation", '<rotation rotation="%d"/>' % rot))
        a.append(("NetName", "<string>%s</string>" % xml_esc(net)))
        self.add("Tunnel", x, y, a)

    @staticmethod
    def gate_pins(n: int) -> Tuple[List[int], int, int]:
        """Digital's GenericShape: input row offsets, output row offset, height.
        Even n leaves the output row (n/2) empty between the two input halves."""
        ins = [i * SIZE if (n % 2 or i < n // 2) else (i + 1) * SIZE for i in range(n)]
        out = (n // 2) * SIZE
        height = (n + 1 if n % 2 == 0 else n) * SIZE
        return ins, out, height

    def gate(self, kind: str, x: int, y: int, n: int) -> Tuple[List[Tuple[int, int]], Tuple[int, int]]:
        """And/Or, wide shape. Returns (input pins, output pin)."""
        a = [("wideShape", "<boolean>true</boolean>")]
        if n != 2:
            a.append(("Inputs", "<int>%d</int>" % n))
        self.add(kind, x, y, a)
        ins, out, _ = self.gate_pins(n)
        return [(x, y + dy) for dy in ins], (x + 4 * SIZE, y + out)

    def not_gate(self, x: int, y: int) -> Tuple[int, int]:
        self.add("Not", x, y)
        return x + 2 * SIZE, y

    def const(self, value: int, x: int, y: int):
        self.add("Const", x, y, [("Value", "<long>%d</long>" % value)])

    def splitter(self, x: int, y: int, in_split: str, out_split: str):
        self.add("Splitter", x, y, [
            ("Input Splitting", "<string>%s</string>" % in_split),
            ("Output Splitting", "<string>%s</string>" % out_split)])

    def testcase(self, x: int, y: int, label: str, data: str):
        self.add("Testcase", x, y, [
            ("Label", "<string>%s</string>" % xml_esc(label)),
            ("Testdata", "<testData>\n            <dataString>%s</dataString>\n          </testData>"
             % xml_esc(data))])

    def render(self) -> str:
        w = self.raw_wires + "".join(
            "    <wire>\n      <p1 x=\"%d\" y=\"%d\"/>\n      <p2 x=\"%d\" y=\"%d\"/>\n    </wire>\n"
            % t for t in self.wires)
        return ('<?xml version="1.0" encoding="utf-8"?>\n<circuit>\n  <version>2</version>\n'
                '  <attributes/>\n  <visualElements>\n%s  </visualElements>\n'
                '  <wires>\n%s  </wires>\n  <measurementOrdering/>\n</circuit>\n'
                % ("".join(self.elems), w))


# --------------------------------------------------------------------------- #
#  PLA signal  <->  template pin bit
# --------------------------------------------------------------------------- #
Groups = List[Tuple[Pin, List[str]]]   # (pin, PLA signal per bit, MSB first)


def bit_net(pin: Pin, k: int) -> str:
    """Internal net name of bit k of a pin (the template-derived name)."""
    return pin.label if pin.bits == 1 else "%s%d" % (pin.label, k)


def map_signals(names: List[str], pins: List[Pin], maps: List[str], what: str) -> Groups:
    """Return, for every template pin, its PLA signal names MSB first."""
    total = sum(p.bits for p in pins)
    side = "input" if what == "ilb" else "output"
    if len(names) != total:
        sys.exit("PLA has %d %s signals but the template %s pins have %d bits: %s"
                 % (len(names), what, side, total, " ".join(repr(p) for p in pins)))
    by_label = {p.label: p for p in pins}
    assigned: Dict[Tuple[str, int], str] = {}     # (label, bit) -> PLA signal

    # explicit --map Label=bN,...,b0
    for spec in maps:
        if "=" not in spec:
            sys.exit("bad --map %r (want Label=bitN,...,bit0)" % spec)
        label, bits = spec.split("=", 1)
        label = label.strip()
        if label not in by_label:
            continue                                # may belong to the other side
        pin = by_label[label]
        sigs = [b.strip() for b in bits.split(",") if b.strip()]
        if len(sigs) != pin.bits:
            sys.exit("--map %s: pin has %d bits, got %d names" % (label, pin.bits, len(sigs)))
        for k, s in zip(range(pin.bits - 1, -1, -1), sigs):
            if s not in names:
                sys.exit("--map %s: %r is not a PLA %s signal (have %s)" % (label, s, what, " ".join(names)))
            assigned[(label, k)] = s

    # by name: A  |  In3 / In[3]
    pat = re.compile(r"^(.*?)(?:(\d+)|\[(\d+)\])$")
    for s in names:
        if s in assigned.values():
            continue
        if s in by_label and by_label[s].bits == 1:
            key = (s, 0)
        else:
            m = pat.match(s)
            if not (m and m.group(1) in by_label):
                sys.exit("PLA %s signal %r matches no template %s pin.\n  template %s pins: %s\n"
                         "  name bits <Label><bit> (In3 In2 In1 In0) or use --map Label=bN,...,b0"
                         % (what, s, side, side, " ".join(repr(p) for p in pins)))
            key = (m.group(1), int(m.group(2) or m.group(3)))
            if key[1] >= by_label[key[0]].bits:
                sys.exit("PLA signal %r: pin %s has only %d bits" % (s, key[0], by_label[key[0]].bits))
        if key in assigned:
            sys.exit("template bit %s%d is mapped twice (%r and %r)" % (key[0], key[1], assigned[key], s))
        assigned[key] = s

    groups: Groups = []
    for p in pins:
        sigs = []
        for k in range(p.bits - 1, -1, -1):
            if (p.label, k) not in assigned:
                sys.exit("template bit %s%d has no PLA %s signal" % (p.label, k, what))
            sigs.append(assigned[(p.label, k)])
        groups.append((p, sigs))
    return groups


def positional(pins: List[Pin], prefix: str) -> List[str]:
    """Synthetic names for a PLA without .ilb/.ob: template order, MSB first."""
    return [bit_net(p, k) for p in pins for k in range(p.bits - 1, -1, -1)]


# --------------------------------------------------------------------------- #
#  test data from the original truth table (columns = template pins)
# --------------------------------------------------------------------------- #
def make_testdata(pla: Pla, igroups: Groups, ogroups: Groups, max_rows: int) -> str:
    iidx = {n: i for i, n in enumerate(pla.ilb)}
    oidx = {n: i for i, n in enumerate(pla.ob)}
    rows: Dict[str, str] = {}
    skipped = 0
    for inp, out in pla.cubes:
        if all(c in "-~" for c in out):
            continue
        dc = [i for i, c in enumerate(inp) if c == "-"]
        if len(dc) > 12:
            skipped += 1
            continue
        for fill in itertools.product("01", repeat=len(dc)):
            bits = list(inp)
            for i, f in zip(dc, fill):
                bits[i] = f
            key = "".join(bits)
            cols = []
            for pin, sigs in igroups:
                cols.append(str(int("".join(bits[iidx[s]] for s in sigs), 2)))
            ok = True
            for pin, sigs in ogroups:
                vals = [out[oidx[s]] for s in sigs]
                if all(v in "-~" for v in vals):
                    cols.append("X")
                elif any(v in "-~" for v in vals):
                    ok = False  # partial don't-care inside a bus: not expressible
                else:
                    cols.append(str(int("".join(vals), 2)))
            if not ok:
                skipped += 1
                continue
            rows[key] = " ".join(cols)   # later rows override (.type fr/fd)
    if skipped:
        print("warning: %d truth-table rows not testable (partial don't-care in a bus)" % skipped,
              file=sys.stderr)
    lines = [" ".join([g[0].label for g in igroups] + [g[0].label for g in ogroups])]
    lines += [rows[k] for k in sorted(rows)][:max_rows]
    return "\n".join(lines)


# --------------------------------------------------------------------------- #
#  circuit generation
# --------------------------------------------------------------------------- #
CHAR_PX = 11  # rough width of one character of a tunnel label, for column spacing


def grid(v: float) -> int:
    return int(-(-v // SIZE)) * SIZE


def term_name(lits: List[Tuple[str, bool]]) -> str:
    """Product term as an expression:  Selector1·Selector0'·In2"""
    return "·".join(n + ("'" if neg else "") for n, neg in lits) if lits else "1"


def build(tpl: Template, pla_min: Pla, igroups: Groups, ogroups: Groups,
          keep_pin_pos: bool, keep_others: bool) -> Dig:
    d = Dig()
    G = SIZE

    # nets carry the PLA signal names (S1, In3, O0 ...); bit k of a pin -> that name
    sig_net: Dict[str, str] = {s: s for _, sigs in igroups + ogroups for s in sigs}
    bit_sig: Dict[Tuple[str, int], str] = {}
    for pin, sigs in igroups + ogroups:
        for k, s in zip(range(pin.bits - 1, -1, -1), sigs):
            bit_sig[(pin.label, k)] = s

    # product terms: literals (net, negated) and the nets each output sums
    terms: List[List[Tuple[str, bool]]] = []
    for inp, _ in pla_min.cubes:
        terms.append([(sig_net[pla_min.ilb[i]], c == "0") for i, c in enumerate(inp) if c in "01"])
    term_nets = [term_name(t) for t in terms]
    sums: List[Tuple[str, List[str]]] = []          # (output bit net, term nets)
    for j, oname in enumerate(pla_min.ob):
        sums.append((sig_net[oname], [term_nets[k] for k, (_, out) in enumerate(pla_min.cubes) if out[j] == "1"]))

    # ---- where the template pins go ------------------------------------------
    x0, y0 = 0, 0
    if keep_pin_pos:
        for p in tpl.pins:                       # pins stay put, a tunnel carries each label
            d.add_raw(p.xml)
            dx, dy = p.free_dir()
            tx, ty = p.x + dx * G, p.y + dy * G
            d.tunnel(p.label, tx, ty, rot=p.rot if p.kind == "In" else (p.rot + 2) % 4)
            d.wire(p.x, p.y, tx, ty)
        if keep_others:
            for b in tpl.others:
                d.add_raw(b)
            d.raw_wires = tpl.wires_xml
        _, _, _, max_y = tpl.bbox(keep_others)
        y0 = grid(max_y + 8 * G)

    # ---- column spacing from the longest labels --------------------------------
    lit_len = max(len(n) for n in sig_net.values())
    trm_len = max(len(n) for n in term_nets)
    out_len = max(len(net) for net, _ in sums)
    xi = x0                                   # In pins (or bus tunnels)
    xb = xi + 3 * G                           # bit tunnels after the splitter
    xt = xb + grid(2 * (lit_len + 1) * CHAR_PX + 3 * G)  # literal tunnels (label to the left)
    xg = xt + 2 * G                           # And gates
    xtn = xg + 5 * G                          # term-name tunnels (label to the right)
    xot = xtn + grid(2 * trm_len * CHAR_PX + 3 * G)  # Or inputs (label to the left)
    xo = xot + 3 * G                          # Or gates
    xon = xo + 5 * G                          # output-bit tunnels (label to the right)
    xq = xon + grid(2 * out_len * CHAR_PX + 3 * G)  # bit tunnels before the joining splitter
    xout = xq + 4 * G                         # Out pins

    # ---- inputs: pin -> splitter -> bit tunnels -------------------------------
    y = y0
    for pin, sigs in igroups:
        if keep_pin_pos:
            d.tunnel(pin.label, xi, y, rot=2)
        else:
            d.add_raw(pin.xml_at(xi, y))
        if pin.bits == 1:
            if keep_pin_pos and sigs[0] == pin.label:
                y += 2 * G
                continue                          # the pin's own net is the literal
            d.tunnel(sigs[0], xi + 2 * G, y)
            d.wire(xi, y, xi + 2 * G, y)
            y += 2 * G
            continue
        d.splitter(xi + 2 * G, y, str(pin.bits), ",".join(["1"] * pin.bits))
        d.wire(xi, y, xi + 2 * G, y)
        for k in range(pin.bits):                 # splitter output k = bit k (LSB on top)
            d.tunnel(bit_sig[(pin.label, k)], xb, y + k * G)
        y += (pin.bits + 1) * G
    negated = sorted({n for t in terms for n, neg in t if neg})   # one Not per signal
    for n in negated:
        d.tunnel(n, xi, y, rot=2)
        nx, ny = d.not_gate(xi + G, y)
        d.wire(xi, y, xi + G, y)
        d.tunnel(n + "'", nx, ny)
        y += G

    # ---- product terms --------------------------------------------------------
    y = y0
    for lits, net in zip(terms, term_nets):
        if not lits:                              # constant 1
            d.const(1, xg, y)
            d.tunnel(net, xg + G, y)
            d.wire(xg, y, xg + G, y)
            y += 2 * G
        elif len(lits) == 1:
            pass                                  # a literal (In3 or In3') is already a net
        else:
            pins, (ox, oy) = d.gate("And", xg, y, len(lits))
            for (px, yy), (sig, neg) in zip(pins, lits):
                d.tunnel(sig + ("'" if neg else ""), xt, yy, rot=2)
                d.wire(xt, yy, xg, yy)
            d.tunnel(net, xtn, oy)
            d.wire(ox, oy, xtn, oy)
            y += d.gate_pins(len(lits))[2] + G

    # ---- sums -----------------------------------------------------------------
    y = y0
    for net, tn in sums:
        if not tn:
            d.const(0, xo, y)
            src = (xo, y)
            y += 2 * G
        elif len(tn) == 1:
            d.tunnel(tn[0], xot, y, rot=2)
            src = (xot, y)
            y += 2 * G
        else:
            pins, (ox, oy) = d.gate("Or", xo, y, len(tn))
            for (px, py), t in zip(pins, tn):
                d.tunnel(t, xot, py, rot=2)
                d.wire(xot, py, xo, py)
            src = (ox, oy)
            y += d.gate_pins(len(tn))[2] + G
        d.tunnel(net, xon, src[1])
        d.wire(src[0], src[1], xon, src[1])

    # ---- outputs: bit tunnels -> splitter -> pin ------------------------------
    y = y0
    for pin, sigs in ogroups:
        if pin.bits == 1:
            d.tunnel(sigs[0], xq, y, rot=2)
            src = (xq, y)
        else:
            d.splitter(xq + G, y, ",".join(["1"] * pin.bits), str(pin.bits))
            for k in range(pin.bits):
                d.tunnel(bit_sig[(pin.label, k)], xq, y + k * G, rot=2)
                d.wire(xq, y + k * G, xq + G, y + k * G)
            src = (xq + 2 * G, y)
        if keep_pin_pos:
            d.tunnel(pin.label, xout, y)
        else:
            d.add_raw(pin.xml_at(xout, y))
        d.wire(src[0], src[1], xout, y)
        y += (pin.bits + 1) * G if pin.bits > 1 else 2 * G
    return d


def build_testfile(title: str, testdata: str) -> str:
    d = Dig()
    d.testcase(0, 0, title, testdata)
    return d.render()


# --------------------------------------------------------------------------- #
#  espresso: try several strategies, keep the cheapest circuit
# --------------------------------------------------------------------------- #
STRATEGIES = ["", "-Dexact", "-estrong", "-Dso", "-Dso_both"]


def circuit_cost(p: Pla) -> Tuple[int, int, int]:
    """(gate inputs, terms, literals): what the SOP circuit will cost."""
    lits = sum(c in "01" for inp, _ in p.cubes for c in inp)
    or_in = sum(c == "1" for _, out in p.cubes for c in out)
    return lits + or_in, len(p.cubes), lits


def minimise(pla_path: str, espresso: str, extra: List[str], names: Tuple[List[str], List[str]]) -> Tuple[Pla, str, str]:
    """Run espresso with the given flags, or with every strategy in STRATEGIES, and
    return (best Pla, flags used, raw espresso output)."""
    tries = [extra] if extra else [s.split() for s in STRATEGIES]
    best = None
    for flags in tries:
        text = run_espresso(pla_path, espresso, flags)
        p = parse_pla(text)
        p.ilb, p.ob = names
        cost = circuit_cost(p)
        if best is None or cost < best[0]:
            best = (cost, p, " ".join(flags), text)
    return best[1], best[2], best[3]


# --------------------------------------------------------------------------- #
#  Digital CLI
# --------------------------------------------------------------------------- #
def find_digital(explicit: Optional[str], near: str) -> Optional[str]:
    if explicit:
        return explicit
    if os.environ.get("DIGITAL_JAR"):
        return os.environ["DIGITAL_JAR"]
    d = os.path.abspath(os.path.dirname(near) or ".")
    for _ in range(6):
        cand = os.path.join(d, "Digital", "Digital.jar")
        if os.path.exists(cand):
            return cand
        parent = os.path.dirname(d)
        if parent == d:
            break
        d = parent
    return None


def run_digital_test(jar: str, dig: str, tests: Optional[str] = None) -> bool:
    cmd = ["java", "-cp", jar, "CLI", "test", "-circ", dig, "-verbose"]
    if tests:
        cmd += ["-tests", tests]
    r = subprocess.run(cmd, capture_output=True, text=True)
    msg = "\n".join(l for l in (r.stdout + r.stderr).splitlines() if not l.startswith("WARNING"))
    print(msg.strip())
    return r.returncode == 0


def check_interface(dig_path: str, tpl: Template) -> bool:
    got = Template(dig_path)
    if got.signature() == tpl.signature():
        print("interface OK: %s" % tpl.interface())
        return True
    print("INTERFACE MISMATCH\n  template: %s\n  %s: %s" % (tpl.interface(), dig_path, got.interface()))
    return False


# --------------------------------------------------------------------------- #
def cmd_gen(args):
    tpl = Template(args.template)
    if not tpl.pins:
        sys.exit("%s has no In/Out pins" % args.template)
    out = args.out or os.path.splitext(args.pla)[0] + ".dig"
    if os.path.abspath(out) == os.path.abspath(args.template) and not args.force:
        sys.exit("refusing to overwrite the template %s (use --force)" % out)

    pla_orig = parse_pla(open(args.pla).read())
    if not pla_orig.ilb:
        pla_orig.ilb = positional(tpl.inputs, "i")
        print("no .ilb: inputs taken positionally as", " ".join(pla_orig.ilb))
    if not pla_orig.ob:
        pla_orig.ob = positional(tpl.outputs, "o")
        print("no .ob: outputs taken positionally as", " ".join(pla_orig.ob))
    maps = pla_orig.maps + args.map
    igroups = map_signals(pla_orig.ilb, tpl.inputs, maps, "ilb")
    ogroups = map_signals(pla_orig.ob, tpl.outputs, maps, "ob")

    if args.no_espresso:
        pla_min, flags = pla_orig, "(none)"
    else:
        pla_min, flags, min_text = minimise(args.pla, args.espresso, args.espresso_args.split(),
                                            (pla_orig.ilb, pla_orig.ob))
        if args.save_min:
            open(args.save_min, "w").write(min_text)

    dig = build(tpl, pla_min, igroups, ogroups, args.keep_pin_pos, args.keep_others)
    os.makedirs(os.path.dirname(os.path.abspath(out)) or ".", exist_ok=True)
    open(out, "w").write(dig.render())

    cost, nterms, nlits = circuit_cost(pla_min)
    n_and = sum(1 for t in pla_min.cubes if sum(c in "01" for c in t[0]) > 1)
    n_or = sum(1 for j in range(pla_min.no) if sum(o[j] == "1" for _, o in pla_min.cubes) > 1)
    n_not = len({(i, "0") for inp, _ in pla_min.cubes for i, c in enumerate(inp) if c == "0"})
    print("%s: espresso %s -> %d terms, %d literals, %d gate inputs  (%d AND, %d OR, %d NOT)"
          % (out, flags or "(default)", nterms, nlits, cost, n_and, n_or, n_not))

    ok = check_interface(out, tpl)
    if ok and not args.no_test:
        title = os.path.splitext(os.path.basename(args.pla))[0]
        testdata = make_testdata(pla_orig, igroups, ogroups, args.max_test_rows)
        test_path = args.save_test or os.path.join(tempfile.gettempdir(), "pla2dig_%s.test.dig" % title)
        open(test_path, "w").write(build_testfile(title, testdata))
        jar = find_digital(args.digital, args.template)
        if jar:
            ok = run_digital_test(jar, out, test_path)
        else:
            print("Digital.jar not found: skipped test (use --digital or DIGITAL_JAR)")
        if not args.save_test:
            os.remove(test_path)
    sys.exit(0 if ok else 1)


def cmd_check(args):
    tpl = Template(args.template)
    ok = check_interface(args.dig, tpl)
    jar = find_digital(args.digital, args.template)
    if jar and args.tests:
        ok = run_digital_test(jar, args.dig, args.tests) and ok
    elif jar and "<elementName>Testcase</elementName>" in open(args.dig).read():
        ok = run_digital_test(jar, args.dig) and ok
    sys.exit(0 if ok else 1)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)

    g = sub.add_parser("gen", help="build a .dig from a .pla using the template's pins")
    g.add_argument("pla")
    g.add_argument("--template", "-t", required=True, help="Template-0N.dig from the lab")
    g.add_argument("-o", "--out", help="output .dig (default: <pla>.dig)")
    g.add_argument("--map", action="append", default=[], metavar="Label=bN,...,b0",
                   help="PLA names for a template pin, MSB first (for legacy .pla names)")
    g.add_argument("--espresso", default="espresso")
    g.add_argument("--espresso-args", default="",
                   help="use exactly these espresso flags instead of trying %s" % " / ".join(repr(s) for s in STRATEGIES))
    g.add_argument("--no-espresso", action="store_true", help="input is already minimised")
    g.add_argument("--save-min", metavar="FILE", help="also save the minimised PLA")
    g.add_argument("--keep-pin-pos", action="store_true",
                   help="leave the template pins where they are (default: move them next to the logic)")
    g.add_argument("--keep-others", action="store_true",
                   help="with --keep-pin-pos: keep the template's other elements/wires too")
    g.add_argument("--no-test", action="store_true", help="skip the Digital test run")
    g.add_argument("--save-test", metavar="FILE", help="keep the generated test .dig (default: temporary)")
    g.add_argument("--max-test-rows", type=int, default=4096)
    g.add_argument("--digital", metavar="Digital.jar", help="(auto-detected if omitted)")
    g.add_argument("--force", action="store_true", help="allow overwriting the template")
    g.set_defaults(func=cmd_gen)

    c = sub.add_parser("check", help="compare a .dig's pins with the template and run tests")
    c.add_argument("dig")
    c.add_argument("--template", "-t", required=True)
    c.add_argument("--tests", metavar="TEST.dig", help="test file (e.g. from gen --save-test)")
    c.add_argument("--digital", metavar="Digital.jar")
    c.set_defaults(func=cmd_check)

    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
