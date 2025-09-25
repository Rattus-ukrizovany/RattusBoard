# 🔌 RattusBoard Split Wiring Guide

*Wiring instructions for left (master) and right (slave) halves.  
See layout: [image3](image3) (user's perspective, thumb cluster = bottom row).*

---

## 📋 Physical Layout Reference

- **Thumb cluster** (orange) = bottom row, closest to user.
- **Main grid** = rows above thumb cluster.
- **Columns** = numbered left to right from user view.
- **Right half** includes trackball and encoder, positioned to right of thumb keys.

---

# ⬅️ Left Half (Master)

**Visual (left side in [image3](image3)):**

```
USER
↑
┌─────┬─────┬─────┬─────┬─────┬─────┐  ← Row 4 (Top)
│ R4C0│ R4C1│ R4C2│ R4C3│ R4C4│ R4C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ R3C0│ R3C1│ R3C2│ R3C3│ R3C4│ R3C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ R2C0│ R2C1│ R2C2│ R2C3│ R2C4│ R2C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ R1C0│ R1C1│ R1C2│ R1C3│ R1C4│ R1C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ T0  │ T1  │ T2  │     │     │     │  ← Row 0 (Thumb, orange)
└─────┴─────┴─────┴─────┴─────┴─────┘
Col0  Col1  Col2  Col3  Col4  Col5
(GP9  GP10  GP11  GP12  GP13  GP14)
```
- T0, T1, T2: Thumb keys = Row 0 (GP6), Col 0–2 (GP9–GP11)
- Main grid: Rows 1–4 (GP2–GP5), Col 0–5 (GP9–GP14)

### Left Half Matrix Pinout

| Pin   | Function        | Connection                         |
|-------|-----------------|------------------------------------|
| GP2   | Row 1           | Main Grid Row 1                    |
| GP3   | Row 2           | Main Grid Row 2                    |
| GP4   | Row 3           | Main Grid Row 3                    |
| GP5   | Row 4           | Main Grid Row 4                    |
| GP6   | Row 0           | Thumb Cluster (T0–T2, bottom row)  |
| GP9   | Col 0           | Matrix Column 0 (leftmost)         |
| GP10  | Col 1           | Matrix Column 1                    |
| GP11  | Col 2           | Matrix Column 2                    |
| GP12  | Col 3           | Matrix Column 3                    |
| GP13  | Col 4           | Matrix Column 4                    |
| GP14  | Col 5           | Matrix Column 5 (rightmost)        |

**Other connections:**
- GP1  → TRRS Tip (Serial to right half)
- GP21 → GND (Hand detect, left ID)
- GP25 → Status LED (optional)
- 3.3V → TRRS Ring 2 (power out)
- GND  → TRRS Ring 1 (ground)

---

# ➡️ Right Half (Slave)

**Visual (right side in [image3](image3)):**

```
USER
↑
┌─────┬─────┬─────┬─────┬─────┬─────┐  ← Row 4 (Top)
│ R4C0│ R4C1│ R4C2│ R4C3│ R4C4│ R4C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ R3C0│ R3C1│ R3C2│ R3C3│ R3C4│ R3C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ R2C0│ R2C1│ R2C2│ R2C3│ R2C4│ R2C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│ R1C0│ R1C1│ R1C2│ R1C3│ R1C4│ R1C5│
├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │ T3  │ T4  │ T5  │  ← Row 0 (Thumb, orange)
└─────┴─────┴─────┴─────┴─────┴─────┘
Col0  Col1  Col2  Col3  Col4  Col5
(GP15 GP16  GP17  GP18  GP19  GP20)
```
- T3, T4, T5: Thumb keys = Row 0 (GP7), Col 3–5 (GP18–GP20)
- Main grid: Rows 1–4 (GP2–GP5), Col 0–5 (GP15–GP20)
- Trackball/encoder: to the right of T3–T5 (user’s right)

### Right Half Matrix Pinout

| Pin   | Function        | Connection                             |
|-------|-----------------|----------------------------------------|
| GP2   | Row 1           | Main Grid Row 1                        |
| GP3   | Row 2           | Main Grid Row 2                        |
| GP4   | Row 3           | Main Grid Row 3                        |
| GP5   | Row 4           | Main Grid Row 4                        |
| GP7   | Row 0           | Thumb Cluster (T3–T5, bottom row)      |
| GP15  | Col 0           | Matrix Column 0 (leftmost)             |
| GP16  | Col 1           | Matrix Column 1                        |
| GP17  | Col 2           | Matrix Column 2                        |
| GP18  | Col 3           | Matrix Column 3                        |
| GP19  | Col 4           | Matrix Column 4                        |
| GP20  | Col 5           | Matrix Column 5 (rightmost)            |

**Other connections:**
- GP1  → TRRS Tip (Serial from left half)
- GP21 → Floating (Hand detect, right ID)
- GP22 → PMW3360 CS (Trackball chip select)
- GP23 → PMW3360 SCK (Trackball clock)
- GP24 → PMW3360 MOSI (Trackball data out)
- GP25 → PMW3360 MISO (Trackball data in)
- GP26 → Encoder A
- GP27 → Encoder B
- GP28 → Encoder SW (optional)
- GP29 → PMW3360 Motion (optional)
- 3.3V → TRRS Ring 2 (power in)
- GND  → TRRS Ring 1 (ground)

---

## ⚡ Power & Communication

- Left half powers right half via 3.3V through TRRS.
- All grounds must be continuous.
- GP1 is split serial communication on both halves.
- Hand detect: GP21 to GND (left), floating (right).

---

## 🧰 Best Practices & Troubleshooting

- Keep GND solid and continuous.
- Use twisted/shielded TRRS cable.
- Test row/column continuity before powering up.
- Ensure trackball, encoder, and thumb row wiring matches the *bottom row* (closest to user).

---

## 📐 Summary Table

| Side    | Rows      | Columns         | Thumb Row Pin | Main Grid Row Pins    | Column Pins      |
|---------|-----------|-----------------|---------------|----------------------|------------------|
| Left    | 5 (0–4)   | 6 (0–5)         | GP6           | GP2–GP5 (1–4)        | GP9–GP14 (0–5)   |
| Right   | 5 (0–4)   | 6 (0–5)         | GP7           | GP2–GP5 (1–4)        | GP15–GP20 (0–5)  |

---

*See README.md for firmware configuration. Layout and pinouts match [image3](image3): thumb (orange) row = bottom, closest to you!*
