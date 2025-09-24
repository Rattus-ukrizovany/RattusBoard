# 🔌 RattusBoard Split Wiring Guide

*Detailed pin assignments and wiring instructions for left (master) and right (slave) halves*

---

## 📋 Overview

This guide provides comprehensive wiring instructions for the RattusBoard split keyboard. **Each half is fully independent with dedicated pins** - there are no shared matrix connections between halves.

**Key Design Principle: NEW 4×6 MATRIX LAYOUT**
- Each half has its own complete 4×6 matrix (3 main rows + 1 thumb row)
- 42 total keys (21 per half)
- Thumb cluster arrangement: Left (cols 3,4,5), Right (cols 0,1,2)
- Communication only via TRRS cable for coordination
- Each microcontroller manages its own hardware completely

**Important:** Both halves use the same firmware but are differentiated through hardware-based hand detection.

---

## 🖥️ Left Half (Master) Wiring

The left half serves as the master controller and handles USB communication with the host computer.

### Matrix Connections

**Row Pins (GP2-GP5) - New 4×6 Layout:**
```
Row 0: GP2  → Connect to all switches in row 0 (top row)
Row 1: GP3  → Connect to all switches in row 1
Row 2: GP4  → Connect to all switches in row 2  
Row 3: GP5  → Connect to all switches in row 3 (thumb cluster)
```

**Column Pins (GP9-GP14) - New 4×6 Layout:**
```
Col 0: GP9  → Connect to all switches in column 0
Col 1: GP10 → Connect to all switches in column 1
Col 2: GP11 → Connect to all switches in column 2
Col 3: GP12 → Connect to all switches in column 3 (includes thumbs)
Col 4: GP13 → Connect to all switches in column 4 (includes thumbs)
Col 5: GP14 → Connect to all switches in column 5 (includes thumbs)
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
GP21 → Connect to GND (this identifies the left half)
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
| GP5 | Row 3 | Matrix Row 3 (thumb) |
| GP9 | Col 0 | Matrix Column 0 |
| GP10 | Col 1 | Matrix Column 1 |
| GP11 | Col 2 | Matrix Column 2 |
| GP12 | Col 3 | Matrix Column 3 (includes thumbs) |
| GP13 | Col 4 | Matrix Column 4 (includes thumbs) |
| GP14 | Col 5 | Matrix Column 5 (includes thumbs) |
| GP21 | Hand Detect | GND (Left ID) |
| GP28 | Status LED | LED (optional) |
| 3.3V | Power Out | TRRS Ring 2 |
| GND | Ground | TRRS Ring 1 |

---

## 🖱️ Right Half (Slave) Wiring

The right half serves as the slave controller and includes the trackball sensor and rotary encoder.

### Matrix Connections

**Row Pins (GP2-GP5) - New 4×6 Layout:**
```
Row 0: GP2  → Connect to all switches in row 0 (top row)
Row 1: GP3  → Connect to all switches in row 1
Row 2: GP4  → Connect to all switches in row 2
Row 3: GP5  → Connect to all switches in row 3 (thumb cluster)
```

**Column Pins (GP15-GP20) - New 4×6 Layout:**
```
Col 0: GP15 → Connect to all switches in column 0 (includes thumbs)
Col 1: GP16 → Connect to all switches in column 1 (includes thumbs) 
Col 2: GP17 → Connect to all switches in column 2 (includes thumbs)
Col 3: GP18 → Connect to all switches in column 3
Col 4: GP19 → Connect to all switches in column 4
Col 5: GP20 → Connect to all switches in column 5
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
GP21 → Leave floating/unconnected (this identifies the right half)
```

### PMW3360 Trackball Sensor

**SPI Interface:**
```
GP22 → CS (Chip Select)
GP23 → SCK (Serial Clock)
GP24 → MOSI (Master Out Slave In)
GP25 → MISO (Master In Slave Out)
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
GP26 → Encoder Pin A (quadrature signal A)
GP27 → Encoder Pin B (quadrature signal B)
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
| GP5 | Row 3 | Matrix Row 3 (thumb) |
| GP15 | Col 0 | Matrix Column 0 (includes thumbs) |
| GP16 | Col 1 | Matrix Column 1 (includes thumbs) |
| GP17 | Col 2 | Matrix Column 2 (includes thumbs) |
| GP18 | Col 3 | Matrix Column 3 |
| GP19 | Col 4 | Matrix Column 4 |
| GP20 | Col 5 | Matrix Column 5 |
| GP21 | Hand Detect | Floating (Right ID) |
| GP22 | PMW3360 CS | Trackball Chip Select |
| GP23 | PMW3360 SCK | Trackball Serial Clock |
| GP24 | PMW3360 MOSI | Trackball Data Out |
| GP25 | PMW3360 MISO | Trackball Data In |
| GP26 | Encoder A | Rotary Encoder Pin A |
| GP27 | Encoder B | Rotary Encoder Pin B |
| GP28 | Encoder SW | Encoder Switch (optional) |
| GP29 | PMW3360 Motion | Motion Detection (optional) |
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