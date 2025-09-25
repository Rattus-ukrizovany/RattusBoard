# 🔌 RattusBoard Split Wiring Guide

*Wiring instructions for left (master) and right (slave) halves, matching the physical and logical layout in [image4](image4).*

---

## 📋 Matrix Layout Overview

- **Main grid:** 3 rows × 6 columns per half (top 18 keys)
- **Thumb row:** 1 row × 3 columns per half (bottom, angled thumb cluster)
- **Columns:** Numbered left to right from user perspective
- **Thumb keys:** are a separate row—“thumb row”—below the grid, not part of row 0 of the main grid

---

# ⬅️ Left Half (Master)

**Logical key arrangement:**

```
USER
↑
┌─────┬─────┬─────┬─────┬─────┬─────┐   ← Main Row 2 (top)
│M2C0 │M2C1 │M2C2 │M2C3 │M2C4 │M2C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M1C0 │M1C1 │M1C2 │M1C3 │M1C4 │M1C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M0C0 │M0C1 │M0C2 │M0C3 │M0C4 │M0C5 │
└─────┴─────┴─────┴─────┴─────┴─────┘
                     T0    T1    T2                       ← Thumb row (angled, bottom)
```
- M = main grid rows (M2 = top, M1 = mid, M0 = bottom); C = column
- T = thumb keys (Ctrl/Esc, Enter, Shift in image4)

**Pin assignments:**
- **Rows:**  
  - GP2: Main Row 0 (bottom of grid)  
  - GP3: Main Row 1 (middle of grid)  
  - GP4: Main Row 2 (top of grid)  
  - GP5: Thumb row (all 3 thumb keys, row 3)
- **Columns:**  
  - GP9  → Column 0 (leftmost)  
  - GP10 → Column 1  
  - GP11 → Column 2  
  - GP12 → Column 3  
  - GP13 → Column 4  
  - GP14 → Column 5 (rightmost)

| Pin   | Function   | Description                       |
|-------|------------|-----------------------------------|
| GP2   | Main Row 0 | Bottom main grid row              |
| GP3   | Main Row 1 | Middle main grid row              |
| GP4   | Main Row 2 | Top main grid row                 |
| GP5   | Thumb Row  | All thumb keys (T0, T1, T2)       |
| GP9   | Col 0      | Leftmost column                   |
| GP10  | Col 1      | Column 1                          |
| GP11  | Col 2      | Column 2                          |
| GP12  | Col 3      | Column 3                          |
| GP13  | Col 4      | Column 4                          |
| GP14  | Col 5      | Rightmost column                  |

**Other connections:**
- GP1  → TRRS Tip (Serial to right half)
- GP21 → GND (Hand detect, left ID)
- 3.3V → TRRS Ring 2 (power out)
- GND  → TRRS Ring 1 (ground)

---

# ➡️ Right Half (Slave)

**Logical key arrangement:**

```
USER
↑
┌─────┬─────┬─────┬─────┬─────┬─────┐   ← Main Row 2 (top)
│M2C0 │M2C1 │M2C2 │M2C3 │M2C4 │M2C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M1C0 │M1C1 │M1C2 │M1C3 │M1C4 │M1C5 │
├─────┼─────┼─────┼─────┼─────┼─────┤
│M0C0 │M0C1 │M0C2 │M0C3 │M0C4 │M0C5 │
└─────┴─────┴─────┴─────┴─────┴─────┘
  T0    T1    T2                       ← Thumb row (angled, bottom)
```
- M = main grid rows; T = thumb keys (Tab, Bksp, Space in image4)

**Pin assignments:**
- **Rows:**  
  - GP2: Main Row 0 (bottom of grid)  
  - GP3: Main Row 1 (middle of grid)  
  - GP4: Main Row 2 (top of grid)  
  - GP5: Thumb row (all 3 thumb keys, row 3)
- **Columns:**  
  - GP15 → Column 0 (leftmost)
  - GP16 → Column 1
  - GP17 → Column 2
  - GP18 → Column 3
  - GP19 → Column 4
  - GP20 → Column 5 (rightmost)

| Pin   | Function   | Description                       |
|-------|------------|-----------------------------------|
| GP2   | Main Row 0 | Bottom main grid row              |
| GP3   | Main Row 1 | Middle main grid row              |
| GP4   | Main Row 2 | Top main grid row                 |
| GP5   | Thumb Row  | All thumb keys (T0, T1, T2)       |
| GP15  | Col 0      | Leftmost column                   |
| GP16  | Col 1      | Column 1                          |
| GP17  | Col 2      | Column 2                          |
| GP18  | Col 3      | Column 3                          |
| GP19  | Col 4      | Column 4                          |
| GP20  | Col 5      | Rightmost column                  |

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
- Ensure thumb row wiring matches the *thumb row* (bottom, angled keys).

---

*See README.md for firmware configuration. Layout and pinouts match [image4](image4): thumb (angled) row is separate and at the bottom, not part of the main grid!*
