# 2110104 Computer Programming

Solutions in C++, grouped by topic. Each problem lives in its own folder (`main.cpp` + CPH test cases in `.cph/`).

## Exercises

| Topic | Problems |
|---|---|
| [00_Basics](Exercises/00_Basics) — Basics & Flowchart | [`Flowchart`](Exercises/00_Basics/Flowchart), [`P1_Flowchart_01`](Exercises/00_Basics/P1_Flowchart_01), [`hello`](Exercises/00_Basics/hello) |
| [01_Expr_Str](Exercises/01_Expr_Str) — Expressions & Strings (intro) | [`01_Expr_11`](Exercises/01_Expr_Str/01_Expr_11), [`01_Expr_12`](Exercises/01_Expr_Str/01_Expr_12), [`01_Expr_13`](Exercises/01_Expr_Str/01_Expr_13), [`01_Expr_14`](Exercises/01_Expr_Str/01_Expr_14), [`01_Expr_15`](Exercises/01_Expr_Str/01_Expr_15), [`01_Expr_21`](Exercises/01_Expr_Str/01_Expr_21), [`01_Expr_22`](Exercises/01_Expr_Str/01_Expr_22), [`01_Str_11`](Exercises/01_Expr_Str/01_Str_11), [`01_Str_31`](Exercises/01_Expr_Str/01_Str_31) |
| [02_If](Exercises/02_If) — Conditionals | [`02_If_11`](Exercises/02_If/02_If_11), [`02_If_12`](Exercises/02_If/02_If_12), [`02_If_12_MobileNumber`](Exercises/02_If/02_If_12_MobileNumber), [`02_If_13`](Exercises/02_If/02_If_13), [`02_If_14`](Exercises/02_If/02_If_14), [`02_If_16`](Exercises/02_If/02_If_16), [`02_If_17`](Exercises/02_If/02_If_17), [`02_If_21`](Exercises/02_If/02_If_21), [`02_If_31`](Exercises/02_If/02_If_31), [`02_If_FC_11`](Exercises/02_If/02_If_FC_11) |
| [03_Loop](Exercises/03_Loop) — Loops | [`03_Loop_11`](Exercises/03_Loop/03_Loop_11), [`03_Loop_12`](Exercises/03_Loop/03_Loop_12), [`03_Loop_13`](Exercises/03_Loop/03_Loop_13), [`03_Loop_14`](Exercises/03_Loop/03_Loop_14), [`03_Loop_15`](Exercises/03_Loop/03_Loop_15), [`03_Loop_16`](Exercises/03_Loop/03_Loop_16), [`03_Loop_21`](Exercises/03_Loop/03_Loop_21), [`03_Loop_22`](Exercises/03_Loop/03_Loop_22), [`03_Loop_23`](Exercises/03_Loop/03_Loop_23) |
| [04_Array](Exercises/04_Array) — Arrays | [`04_Array_23`](Exercises/04_Array/04_Array_23) |
| [05_String](Exercises/05_String) — Strings | [`05_String_21`](Exercises/05_String/05_String_21), [`05_String_23`](Exercises/05_String/05_String_23), [`05_String_24`](Exercises/05_String/05_String_24) |
| [06_Vector](Exercises/06_Vector) — Vectors | [`06_Vector_24`](Exercises/06_Vector/06_Vector_24), [`06_Vector_25`](Exercises/06_Vector/06_Vector_25), [`06_Vector_33`](Exercises/06_Vector/06_Vector_33), [`06_Vector_36`](Exercises/06_Vector/06_Vector_36) |
| [07_Map](Exercises/07_Map) — Map | [`07_Map_11`](Exercises/07_Map/07_Map_11) |
| [07_Set](Exercises/07_Set) — Set | [`07_Set_11`](Exercises/07_Set/07_Set_11), [`07_Set_12`](Exercises/07_Set/07_Set_12), [`07_Set_13`](Exercises/07_Set/07_Set_13), [`07_Set_21`](Exercises/07_Set/07_Set_21) |

## Exams

| Set | Problems |
|---|---|
| [CM_2024](Exams/CM_2024) | [`CM01`](Exams/CM_2024/CM01), [`CM02`](Exams/CM_2024/CM02), [`CM03`](Exams/CM_2024/CM03), [`CM04`](Exams/CM_2024/CM04) |
| [CM_69](Exams/CM_69) | [`CM01`](Exams/CM_69/CM01), [`CM04`](Exams/CM_69/CM04) |
| [exam67_1](Exams/exam67_1) | [`P3`](Exams/exam67_1/P3), [`P4`](Exams/exam67_1/P4) |

## Final

- [`Stack/calculator.cpp`](Final/Stack/calculator.cpp) — stack-based calculator (WIP)

## Build

```sh
g++ -std=c++17 -O2 main.cpp -o main.bin && ./main.bin
```

Compiled binaries (`*.bin`, `*.exe`, `main`) are git-ignored.
