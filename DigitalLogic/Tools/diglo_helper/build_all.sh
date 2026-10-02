#!/bin/bash
# Build all four Lab03 answers from the templates and test them with Digital.
#   ./build_all.sh            -> Lab03/out/01.dig .. 04.dig
set -u
cd "$(dirname "$0")"
PY=${PYTHON:-python3}
$PY -c 'import sys' 2>/dev/null || PY=/usr/bin/python3
LAB=../../Labs/Lab03
OUT=$LAB/out
fail=0
run() {  # run <n> <pla>
    echo "=== Lab03-$1"
    $PY pla2dig.py gen "labs/$2" --template "$LAB/Template-$1.dig" -o "$OUT/$1.dig" || fail=1
    echo
}
run 01 lab01_sevenseg.pla
run 02 lab02_ascii.pla
run 03 lab03_encoder.pla
run 04 lab04_hamming.pla
if [ $fail -ne 0 ]; then echo "*** SOME LABS FAILED ***"; exit 1; fi
echo "all 4 labs built and tested: $OUT/"
