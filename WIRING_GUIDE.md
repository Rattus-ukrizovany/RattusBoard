# 🔌 RattusBoard Split Wiring Guide

*Detailed pin assignments and wiring instructions for left (master) and right (slave) halves*

---

## 📋 Overview

This guide provides comprehensive wiring instructions for the RattusBoard split keyboard. **Each half is fully independent with dedicated pins** - there are no shared matrix connections between halves.

**Key Design Principle: FULLY INDEPENDENT HALVES**
- Each half has its own complete 3×7 matrix
- No shared row or column pins between halves
- Communication only via TRRS cable for coordination
- Each microcontroller manages its own hardware completely

**Important:** Both halves use the same firmware but are differentiated through hardware-based hand detection.

---

## 🖥️ Left Half (Master) Wiring

The left half serves as the master controller and handles USB communication with the host computer.

### Matrix Connections

**Row Pins (GP2-GP8):**
```
Row 0: GP2  → Connect to all switches in row 0 (top row)
Row 1: GP3  → Connect to all switches in row 1
Row 2: GP4  → Connect to all switches in row 2
Row 3: GP5  → Connect to all switches in row 3
Row 4: GP6  → Connect to all switches in row 4
Row 5: GP7  → Connect to all switches in row 5
Row 6: GP8  → Connect to all switches in row 6 (thumb cluster)
```

**Column Pins (GP9-GP11):**
```
Col 0: GP9  → Connect to all switches in column 0 (leftmost)
Col 1: GP10 → Connect to all switches in column 1 (middle)
Col 2: GP11 → Connect to all switches in column 2 (rightmost)
```

### Split Communication

**TRRS Jack Connection:**
```
GP1  → TRRS Tip (Serial communication to right half)
GND  → TRRS Ring 1 (Ground connection)
3.3V → TRRS Ring 2 (Power supply to right half)
NC   → TRRS Sleeve (Not connected)
```

### Hand Detection

**Split Detection Pin:**
```
GP16 → Connect to GND (this identifies the left half)
```

### Power and USB

**USB-C Connection:**
```
USB-C connector → Connect to Pico's native USB pins
GP25 → Status LED (optional)
```

**Power Distribution:**
- 3.3V rail powers both halves via TRRS connection
- GND must be continuous between halves
- Left half draws power from USB host

### Left Half Pin Summary

| Pin | Function | Connection |
|-----|----------|------------|
| GP1 | Split Serial | TRRS Tip |
| GP2 | Row 0 | Matrix Row 0 |
| GP3 | Row 1 | Matrix Row 1 |
| GP4 | Row 2 | Matrix Row 2 |
| GP5 | Row 3 | Matrix Row 3 |
| GP6 | Row 4 | Matrix Row 4 |
| GP7 | Row 5 | Matrix Row 5 |
| GP8 | Row 6 | Matrix Row 6 (thumb) |
| GP9 | Col 0 | Matrix Column 0 |
| GP10 | Col 1 | Matrix Column 1 |
| GP11 | Col 2 | Matrix Column 2 |
| GP16 | Hand Detect | GND (Left ID) |
| GP25 | Status LED | LED (optional) |
| 3.3V | Power Out | TRRS Ring 2 |
| GND | Ground | TRRS Ring 1 |

---

## 🖱️ Right Half (Slave) Wiring

The right half serves as the slave controller and includes the trackball sensor and rotary encoder.

### Matrix Connections

**Row Pins (GP2-GP8) - Same as Left:**
```
Row 0: GP2  → Connect to all switches in row 0 (top row)
Row 1: GP3  → Connect to all switches in row 1
Row 2: GP4  → Connect to all switches in row 2
Row 3: GP5  → Connect to all switches in row 3
Row 4: GP6  → Connect to all switches in row 4
Row 5: GP7  → Connect to all switches in row 5
Row 6: GP8  → Connect to all switches in row 6 (thumb cluster)
```

**Column Pins (GP12-GP14):**
```
Col 3: GP12 → Connect to all switches in column 0 (leftmost on right half)
Col 4: GP13 → Connect to all switches in column 1 (middle on right half)
Col 5: GP14 → Connect to all switches in column 2 (rightmost on right half)
```

### Split Communication

**TRRS Jack Connection:**
```
GP1  → TRRS Tip (Serial communication from left half)
GND  → TRRS Ring 1 (Ground connection)
3.3V → TRRS Ring 2 (Power from left half)
NC   → TRRS Sleeve (Not connected)
```

### Hand Detection

**Split Detection Pin:**
```
GP16 → Leave floating/unconnected (this identifies the right half)
```

### PMW3360 Trackball Sensor

**SPI Interface:**
```
GP17 → CS (Chip Select)
GP18 → SCK (Serial Clock)
GP19 → MOSI (Master Out Slave In)
GP20 → MISO (Master In Slave Out)
3.3V → VCC (Power)
GND  → GND (Ground)
```

**Additional PMW3360 Connections:**
```
GP23 → Motion pin (optional, for motion detection)
3.3V → Reset pin (through 10kΩ resistor)
```

### Rotary Encoder

**Encoder Connections:**
```
GP21 → Encoder Pin A (quadrature signal A)
GP22 → Encoder Pin B (quadrature signal B)
GND  → Encoder Common/Ground
```

**Encoder Switch (if present):**
```
GP24 → Encoder switch pin (optional push button)
GND  → Encoder switch ground
```

### Right Half Pin Summary

| Pin | Function | Connection |
|-----|----------|------------|
| GP1 | Split Serial | TRRS Tip |
| GP2 | Row 0 | Matrix Row 0 |
| GP3 | Row 1 | Matrix Row 1 |
| GP4 | Row 2 | Matrix Row 2 |
| GP5 | Row 3 | Matrix Row 3 |
| GP6 | Row 4 | Matrix Row 4 |
| GP7 | Row 5 | Matrix Row 5 |
| GP8 | Row 6 | Matrix Row 6 (thumb) |
| GP12 | Col 3 | Matrix Column 0 |
| GP13 | Col 4 | Matrix Column 1 |
| GP14 | Col 5 | Matrix Column 2 |
| GP16 | Hand Detect | Floating (Right ID) |
| GP17 | PMW3360 CS | Trackball Chip Select |
| GP18 | PMW3360 SCK | Trackball Serial Clock |
| GP19 | PMW3360 MOSI | Trackball Data Out |
| GP20 | PMW3360 MISO | Trackball Data In |
| GP21 | Encoder A | Rotary Encoder Pin A |
| GP22 | Encoder B | Rotary Encoder Pin B |
| GP23 | PMW3360 Motion | Motion Detection (optional) |
| GP24 | Encoder SW | Encoder Switch (optional) |
| 3.3V | Power In | TRRS Ring 2 |
| GND | Ground | TRRS Ring 1 |

---

## ⚡ Power Distribution

### Power Flow
1. **USB Host** → **Left Half Pico** → **TRRS Cable** → **Right Half Pico**
2. Left half receives 5V from USB, regulates to 3.3V
3. 3.3V is shared with right half via TRRS Ring 2
4. Both halves operate at 3.3V logic levels

### Power Requirements
- **Left Half**: ~100mA (matrix scanning, USB communication)
- **Right Half**: ~150mA (matrix scanning, PMW3360, encoder)
- **Total**: ~250mA (well within USB 2.0 500mA limit)

---

## 🔧 Wiring Best Practices

### Critical Requirements
- ⚠️ **All GND connections must be solid and continuous**
- ⚠️ **Use twisted pair or shielded cable for TRRS connection**
- ⚠️ **Keep high-speed SPI signals away from matrix wiring**
- ⚠️ **Test continuity of all connections before powering up**

### Assembly Tips
- 🎨 **Use different colored wires for rows vs columns**
- 🏷️ **Label all connections during assembly**
- 📸 **Take photos before closing the case**
- 🧪 **Use flux for all solder joints**
- 🔬 **Test each half independently before connecting**

### Testing Procedure
1. **Visual Inspection**: Check all solder joints for shorts/opens
2. **Continuity Testing**: Verify all matrix connections with multimeter
3. **Power Testing**: Confirm 3.3V present at all required pins
4. **Individual Testing**: Test each half separately with firmware
5. **Split Testing**: Connect halves and verify communication

---

## 🚨 Troubleshooting

### Common Issues

**Split Communication Problems:**
- Check TRRS cable continuity
- Verify GP1 connections on both halves
- Ensure proper hand detection (GP16 to GND on left only)

**Matrix Issues:**
- Verify diode orientation (COL2ROW)
- Check row/column pin assignments
- Test individual switches with multimeter

**Trackball Not Working:**
- Confirm SPI wiring (GP17-GP20)
- Check PMW3360 power supply (3.3V)
- Verify chip select (CS) connection

**Encoder Issues:**
- Check quadrature signals (GP21, GP22)
- Verify encoder power and ground
- Test encoder switch if present (GP24)

### Debug Commands
```bash
# Test matrix scanning
qmk console

# Check split communication
# Look for "matrix_scan_quantum" messages from both halves
```

---

## 📐 Layout Reference

```
Left Half (Master)                Right Half (Slave)
┌─────┬─────┬─────┐              ┌─────┬─────┬─────┐
│ 0,0 │ 0,1 │ 0,2 │              │ 0,3 │ 0,4 │ 0,5 │
├─────┼─────┼─────┤              ├─────┼─────┼─────┤
│ 1,0 │ 1,1 │ 1,2 │              │ 1,3 │ 1,4 │ 1,5 │
├─────┼─────┼─────┤              ├─────┼─────┼─────┤
│ 2,0 │ 2,1 │ 2,2 │              │ 2,3 │ 2,4 │ 2,5 │
├─────┼─────┼─────┤              ├─────┼─────┼─────┤
│ 3,0 │ 3,1 │ 3,2 │              │ 3,3 │ 3,4 │ 3,5 │
├─────┼─────┼─────┤              ├─────┼─────┼─────┤
│ 4,0 │ 4,1 │ 4,2 │              │ 4,3 │ 4,4 │ 4,5 │
├─────┼─────┼─────┤              ├─────┼─────┼─────┤
│ 5,0 │ 5,1 │ 5,2 │              │ 5,3 │ 5,4 │ 5,5 │ 🖱️ Trackball
├─────┼─────┼─────┤              ├─────┼─────┼─────┤
      │ 6,1 │ 6,2 │              │ 6,3 │ 6,4 │      🎛️ Encoder
      └─────┴─────┘              └─────┴─────┘

GP9   GP10  GP11                 GP12  GP13  GP14
Col0  Col1  Col2                 Col3  Col4  Col5
```

Matrix coordinates: (row, column) where row 0-6 and column 0-5

---

*This guide covers the complete wiring specifications for both halves of the RattusBoard. For firmware configuration and flashing instructions, refer to the main README.md file.*