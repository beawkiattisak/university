# diglo_helper — .pla → espresso → Digital .dig ที่ตรงกับ Template ของมหาลัย

ระบบตรวจของมหาลัยดูแค่ **ขา In/Out ของ Template (ชื่อ + จำนวนบิต)** — ไฟล์ Template
ที่แจกมามีแค่ขา In/Out เปล่า ๆ ไม่มี logic ไม่มี Testcase ดังนั้น `pla2dig.py` จะ

1. อ่าน `Template-0N.dig` เก็บขา In/Out ไว้ (label / bits เหมือนเดิมทุกตัวอักษร) ทิ้งอย่างอื่นทั้งหมด
   แล้วย้ายขามาวางชิดวงจร (In ซ้าย, Out ขวา) — ถ้าอยากให้อยู่ที่เดิมใช้ `--keep-pin-pos`
2. รัน `espresso` หลายแบบ (default, `-Dexact`, `-estrong`, `-Dso`, `-Dso_both`) แล้วเลือกผลที่
   วงจรเล็กที่สุด (นับขา input ของ gate รวม) — บังคับแบบเดียวได้ด้วย `--espresso-args`
3. ต่อวงจร SOP: Not หนึ่งตัวต่อสัญญาณ (`In2'`) → And ต่อ product term → Or ต่อ output bit
   ชื่อ Tunnel ใช้ชื่อสัญญาณจาก `.pla` ตรง ๆ (`S1`, `In2'`, `S1·S0'·In2`) — ตั้งสั้น ๆ ได้ตามใจ
4. ตรวจว่า In/Out ของไฟล์ผลลัพธ์ **ตรงกับ Template เป๊ะ** (`interface OK: ...`)
5. สร้าง Testcase จาก truth table ใน `.pla` เป็นไฟล์ชั่วคราวแยกต่างหาก (ไม่ฝังใน .dig ที่ส่ง)
   แล้วรัน `java -cp Digital.jar CLI test -circ out.dig -tests test.dig` ให้ทันที

## ทำทั้ง 4 ข้อของ Lab03 ในคำสั่งเดียว

```sh
cd /Users/kiattisak/Documents/university/university/DigitalLogic/Tools/diglo_helper
./build_all.sh
```

ได้ `Labs/Lab03/out/01.dig … 04.dig` — แต่ละข้อต้องขึ้น `interface OK` และ `passed` ถึงจะถือว่าเสร็จ
ส่งไฟล์ใน `Labs/Lab03/out/` ขึ้นระบบได้เลย

| ข้อ | Template | PLA | ขา |
|---|---|---|---|
| 01 BCD → 7-seg | `Template-01.dig` | `labs/lab01_sevenseg.pla` | `In[4] → A..G` |
| 02 DigLoLab ASCII | `Template-02.dig` | `labs/lab02_ascii.pla` | `In[3] → Z[8]` |
| 03 Binary Encoder | `Template-03.dig` | `labs/lab03_encoder.pla` | `In[4] Selector[2] → Output[4]` |
| 04 Hamming | `Template-04.dig` | `labs/lab04_hamming.pla` | `In[7] → Output[7]` |

## ทำทีละข้อ

```sh
python3 pla2dig.py gen labs/lab03_encoder.pla --template ../../Labs/Lab03/Template-03.dig -o ../../Labs/Lab03/out/03.dig
```

ก่อนอัปโหลด เช็คไฟล์ไหนก็ได้ว่าขาตรง Template (และรัน test ถ้ามีไฟล์ test):

```sh
python3 pla2dig.py gen   labs/lab03_encoder.pla --template ../../Labs/Lab03/Template-03.dig -o ../../Labs/Lab03/out/03.dig --save-test ../../Labs/Lab03/out/03.test.dig
python3 pla2dig.py check ../../Labs/Lab03/out/03.dig    --template ../../Labs/Lab03/Template-03.dig --tests ../../Labs/Lab03/out/03.test.dig
```

(ถ้า `python3` ของ Homebrew พัง ให้ใช้ `/usr/bin/python3` แทน — สคริปต์ไม่ใช้ xml lib)

## เขียน .pla ให้ตรง Template (ข้อใหม่ ๆ)

ตั้งชื่อใน `.ilb` / `.ob` ตามขาของ Template:

* ขา 1 บิต `A` → `A`
* ขา bus `In` 4 บิต → `In3 In2 In1 In0` (MSB ก่อน; `In[3]` ก็ได้)
* ไม่ใส่ `.ilb`/`.ob` เลย → เรียงตามลำดับขาใน Template, MSB ก่อน
* อยากใช้ชื่อสั้น (`S1 S0`, `O3..O0`) → ใส่บรรทัด `#map Selector=S1,S0` / `#map Output=O3,O2,O1,O0`
  ไว้ใน `.pla` (หรือ `--map ...` ตอนรัน) — ชื่อที่เห็นในวงจรจะเป็นชื่อที่ตั้งใน `.pla`

ชื่อไม่ตรงกับ Template = error พร้อมรายชื่อขาให้ทันที ไม่มีทางได้ไฟล์ที่ขาไม่ตรงออกมา

## ตัวเลือกอื่น

| flag | ความหมาย |
|---|---|
| `--digital Digital.jar` | ปกติหาเอง (`$DIGITAL_JAR` หรือ `Digital/Digital.jar` ในโฟลเดอร์แม่ของ Template) |
| `--save-min FILE` | เก็บผล espresso ไว้ดู |
| `--no-espresso` | `.pla` ย่อมาแล้ว |
| `--espresso-args "-Dexact"` | ใช้ flag นี้อย่างเดียว แทนการลองหลายแบบแล้วเลือก |
| `--keep-pin-pos` | ไม่ย้ายขา In/Out ของ Template (วงจรจะถูกวางใต้ขาเดิม เชื่อมด้วย Tunnel) |
| `--keep-others` | (คู่กับ `--keep-pin-pos`) เก็บ element อื่นใน Template ไว้ด้วย — **ห้ามใช้กับไฟล์ที่มี logic ต่อเข้าขา Out อยู่แล้ว** |
| `--save-test FILE` | เก็บไฟล์ Testcase ไว้ (ปกติเป็นไฟล์ชั่วคราวแล้วลบ) เปิดใน Digital กด F8 ก็ได้ |
| `--no-test` | ไม่รัน test |
| `--force` | ยอมเขียนทับ Template (ปกติปฏิเสธ) |

## หมายเหตุข้อ 04 (Hamming)

`labs/lab04_hamming.pla` สร้างจาก `labs/make_hamming_pla.py` (10 codeword × 8 กรณี = 80 แถว)
โดยถือว่า **ตำแหน่ง 1 (p1) ในตารางคือ MSB `In6`** และตำแหน่ง 7 (m4) คือ `In0`
ถ้าระบบตรวจใช้ลำดับกลับกัน ให้สร้างใหม่ด้วย

```sh
cd labs && python3 make_hamming_pla.py --pos1-lsb && cd .. && ./build_all.sh
```
