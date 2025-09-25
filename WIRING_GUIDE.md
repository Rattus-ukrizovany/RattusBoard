# 🔌 RattusBoard Split Wiring Guide

_This guide describes the physical matrix and microcontroller wiring for the RattusBoard split keyboard, matching the 3x6+3 layout in [image4](image4). It is designed for compatibility with ZMK/QMK firmware._

---

## 📋 Matrix Overview

- **Main grid:** 3 rows × 6 columns per half (`row 0` = grid bottom, `row 2` = grid top)
- **Thumbs:** 1 row × 3 columns per half (`row 3` = thumb cluster, angled below main grid)
- **Columns:** Numbered 0–5 (left to right, user’s view) and shared by both main grid and thumb row
- **All matrix pins must match row/col order in your firmware config**

---

# ⬅️ Left Half (Master)

**Physical layout:**
```
USER
↑
┌─────┬─────┬─────┬─────┬─────┬─────┐  ← Row 2 (Top)
│M2C0 │M2C1 │M2C2 │M2C3 │M2C4 │M2C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M1C0 │M1C1 │M1C2 │M1C3 │M1C4 │M1C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M0C0 │M0C1 │M0C2 │M0C3 │M0C4 │M0C5 │
└─────┴─────┴─────┴─────┴─────┴─────┘
                      T0    T1    T2     ← Row 3 (thumbs, angled)
```

**Pinout (suggested for ZMK/QMK):**

| Pin   | Function   | Description                                  |
|-------|------------|----------------------------------------------|
| GP2   | Row 0      | Main grid bottom row                         |
| GP3   | Row 1      | Main grid middle row                         |
| GP4   | Row 2      | Main grid top row                            |
| GP5   | Row 3      | Thumb row (all 3 thumb keys)                 |
| GP9   | Col 0      | Leftmost column                              |
| GP10  | Col 1      | Column 1                                     |
| GP11  | Col 2      | Column 2                                     |
| GP12  | Col 3      | Column 3                                     |
| GP13  | Col 4      | Column 4                                     |
| GP14  | Col 5      | Rightmost column                             |
| GP1   | Split RX/TX| TRRS Tip (serial to right half)              |
| GP21  | Hand detect| Connect to GND (marks as left/master)        |
| 3.3V  | Power      | TRRS Ring 2 (powers right half)              |
| GND   | Ground     | TRRS Ring 1                                  |

---

# ➡️ Right Half (Slave)

**Physical layout:**
```
USER
↑
┌─────┬─────┬─────┬─────┬─────┬─────┐  ← Row 2 (Top)
│M2C0 │M2C1 │M2C2 │M2C3 │M2C4 │M2C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M1C0 │M1C1 │M1C2 │M1C3 │M1C4 │M1C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M0C0 │M0C1 │M0C2 │M0C3 │M0C4 │M0C5 │
└─────┴─────┴─────┴─────┴─────┴─────┘
  T0    T1    T2                       ← Row 3 (thumbs, angled)
```
- **Trackball and encoder are to the right of the thumb cluster.**

**Pinout (matrix + trackball/encoder):**

| Pin   | Function      | Description                                  |
|-------|---------------|----------------------------------------------|
| GP2   | Row 0         | Main grid bottom row                         |
| GP3   | Row 1         | Main grid middle row                         |
| GP4   | Row 2         | Main grid top row                            |
| GP5   | Row 3         | Thumb row (all 3 thumb keys)                 |
| GP15  | Col 0         | Leftmost column                              |
| GP16  | Col 1         | Column 1                                     |
| GP17  | Col 2         | Column 2                                     |
| GP18  | Col 3         | Column 3                                     |
| GP19  | Col 4         | Column 4                                     |
| GP20  | Col 5         | Rightmost column                             |
| GP1   | Split RX/TX   | TRRS Tip (serial from left half)             |
| GP21  | Hand detect   | Floating (marks as right/slave)              |

**Trackball (PMW3360 sensor):**
| Pin   | Function    | Description                 |
|-------|-------------|----------------------------|
| GP22  | CS          | Chip Select                 |
| GP23  | SCK         | Serial Clock                |
| GP24  | MOSI        | SPI Data Out                |
| GP25  | MISO        | SPI Data In                 |
| GP29  | Motion      | Motion IRQ (optional)       |
| 3.3V  | VCC         | Power                       |
| GND   | GND         | Ground                      |
| 3.3V  | Reset       | 10kΩ to 3.3V (see datasheet)|

**Rotary Encoder:**
| Pin   | Function    | Description                 |
|-------|-------------|----------------------------|
| GP26  | Encoder A   | Encoder output A            |
| GP27  | Encoder B   | Encoder output B            |
| GP28  | Encoder SW  | Encoder switch (optional)   |
| GND   | GND         | Encoder common              |

---

## ⚡ Power & Communication

- Left half powers right half via 3.3V through TRRS.
- All grounds must be continuous.
- GP1 is split serial communication (TX/RX) on both halves.
- Hand detect: GP21 to GND (left), floating (right).

---

## 🧰 Notes for ZMK/QMK Firmware

- **Matrix order in firmware must match row/col wiring above.**
- **Rows:** `[GP2, GP3, GP4, GP5]` (grid bottom → grid top, then thumbs)
- **Columns:** `[GP9–GP14]` (left half), `[GP15–GP20]` (right half)
- **Thumb keys:** are assigned to row 3 in your keymap, sharing columns with the main grid.

Example ZMK `matrix_pins:` (left):
```yaml
rows:
  - GP2  # Row 0 (grid bottom)
  - GP3  # Row 1
  - GP4  # Row 2 (grid top)
  - GP5  # Row 3 (thumbs)
columns:
  - GP9
  - GP10
  - GP11
  - GP12
  - GP13
  - GP14
```

---

## 🛠️ Troubleshooting & Best Practices

- Test matrix continuity before powering up.
- Keep all GND connections solid and continuous.
- Confirm all trackball/encoder SPI lines match firmware.
- Use a shielded TRRS cable for split serial and power.
- For custom features, see your firmware’s split docs.

---

*See README.md for firmware setup. Pinouts and logic match [image4](image4) and are ready for ZMK/QMK!*
