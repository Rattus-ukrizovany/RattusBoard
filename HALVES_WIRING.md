# 🔌 RattusBoard Split Keyboard Wiring Guide

*Detailed half-specific wiring instructions for the RattusBoard split ergonomic keyboard*

---

## Table of Contents

- [Overview Diagram](#-overview-diagram)
- [Left Half (Master) Wiring](#-left-half-master-wiring)
- [Right Half (Slave) Wiring](#-right-half-slave-wiring)
- [Critical Assembly Guidelines](#-critical-assembly-guidelines)
- [Assembly & Testing Tips](#-assembly--testing-tips)
- [Pin Assignment Summary](#-pin-assignment-summary)
- [Troubleshooting](#-troubleshooting)

---

## 🔍 Overview Diagram

```
Left Half (Master)                    Right Half (Slave)
┌─────────────────────┐              ┌─────────────────────┐
│    [USB-C INPUT]    │              │                     │
│  Raspberry Pi Pico  │◄─── TRRS ───►│  Raspberry Pi Pico  │
│                     │              │                     │
│  Matrix: 3×7        │              │  Matrix: 3×7        │
│  Cols: GP9-GP11     │              │  Cols: GP12-GP14    │
│  Rows: GP2-GP8      │              │  Rows: GP2-GP8      │
│                     │              │                     │
│  Split Pin: GP16→GND│              │  Split Pin: GP16    │
│  TRRS: GP1          │              │  TRRS: GP1          │
│                     │              │                     │
│                     │              │  [PMW3360 SENSOR]   │
│                     │              │  SPI: GP17-GP20     │
│                     │              │                     │
│                     │              │  [ROTARY ENCODER]   │
│                     │              │  Pins: GP21-GP22    │
└─────────────────────┘              └─────────────────────┘
        MASTER                              SLAVE
     (USB Connected)                    (TRRS Powered)
```

**Signal Flow:**
```
Computer ──USB-C──► Left Pico ──TRRS──► Right Pico
                        │                    │
                   Matrix 3×7           Matrix 3×7
                   (Cols 0-2)          (Cols 3-5→0-2)
                                           │
                                    ┌─────────────┐
                                    │ PMW3360     │
                                    │ Trackball   │
                                    └─────────────┘
                                           │
                                    ┌─────────────┐
                                    │ Rotary      │
                                    │ Encoder     │
                                    └─────────────┘
```

---

## 📍 Left Half (Master) Wiring

The left half serves as the master controller, connecting directly to your computer via USB-C and powering both halves through the TRRS connection.

### ⚡ Power & Communication

**USB-C Connection:**
```
┌─────────────────┐
│    USB-C Port   │ ──► Connect to Pico's native USB
│   (Computer)    │
└─────────────────┘
            │
    ┌─────────────────┐
    │ Raspberry Pi    │
    │ Pico (Left)     │
    │ GP25 ────► LED  │ (Optional status indicator)
    └─────────────────┘
```

**TRRS Jack Wiring:**
```
TRRS Jack          Raspberry Pi Pico
┌─────────┐       ┌─────────────────┐
│ Tip     │◄─────►│ GP1 (Serial)    │
│ Ring 1  │◄─────►│ GND (Ground)    │
│ Ring 2  │◄─────►│ 3.3V (Power)    │
│ Sleeve  │       │ NC (Unused)     │
└─────────┘       └─────────────────┘
```

### 🎯 Matrix Connections

**Row Pins (Shared signal names with right half):**
```
    Switch Matrix Layout (Left Half)
    
    Col 0   Col 1   Col 2
Row 0  ⊞  ──  ⊞  ──  ⊞     GP2
       │      │      │  
Row 1  ⊞  ──  ⊞  ──  ⊞     GP3
       │      │      │  
Row 2  ⊞  ──  ⊞  ──  ⊞     GP4
       │      │      │  
Row 3  ⊞  ──  ⊞  ──  ⊞     GP5
       │      │      │  
Row 4  ⊞  ──  ⊞  ──  ⊞     GP6
       │      │      │  
Row 5  ⊞  ──  ⊞  ──  ⊞     GP7
       │      │      │  
Row 6     ⊞     ⊞  ──      GP8 (Thumbs)
       │      │      │  
      GP9    GP10   GP11
```

**Detailed Connections:**
```
Row 0: GP2  → All switches in top row
Row 1: GP3  → All switches in second row
Row 2: GP4  → All switches in third row
Row 3: GP5  → All switches in fourth row
Row 4: GP6  → All switches in fifth row
Row 5: GP7  → All switches in bottom row
Row 6: GP8  → All thumb cluster switches

Col 0: GP9  → All switches in leftmost column
Col 1: GP10 → All switches in middle column
Col 2: GP11 → All switches in rightmost column
```

### 🔧 Critical Configuration

**Hand Detection (Essential!):**
```
GP16 ──┐
       │  Required for firmware to identify
       │  this half as the LEFT/MASTER
       └── GND
```

**Diode Installation:**
```
    For each switch position:
    
    Row Pin ←──┤|── Switch ──← Column Pin
                ▲
            Diode (1N4148)
         Cathode (band) toward row
         Anode toward column
    
    This is COL2ROW configuration
```

---

## 📍 Right Half (Slave) Wiring  

The right half operates as a slave, receiving power and communicating through the TRRS connection. It includes the trackball sensor and rotary encoder.

### ⚡ Power & Communication

**TRRS Jack Wiring (Mirror of left):**
```
TRRS Jack          Raspberry Pi Pico
┌─────────┐       ┌─────────────────┐
│ Tip     │◄─────►│ GP1 (Serial)    │
│ Ring 1  │◄─────►│ GND (Ground)    │
│ Ring 2  │◄─────►│ 3.3V (Power IN) │
│ Sleeve  │       │ NC (Unused)     │
└─────────┘       └─────────────────┘
```

**Power Flow Verification:**
```
Left Pico 3.3V ──TRRS──► Right Pico 3.3V
Left Pico GND  ──TRRS──► Right Pico GND
                │
                └──► Powers PMW3360 & Encoder
```

### 🎯 Matrix Connections

```
    Switch Matrix Layout (Right Half)
    
    Col 0   Col 1   Col 2
Row 0  ⊞  ──  ⊞  ──  ⊞     GP2
       │      │      │  
Row 1  ⊞  ──  ⊞  ──  ⊞     GP3
       │      │      │  
Row 2  ⊞  ──  ⊞  ──  ⊞     GP4
       │      │      │  
Row 3  ⊞  ──  ⊞  ──  ⊞     GP5
       │      │      │  
Row 4  ⊞  ──  ⊞  ──  ⊞     GP6
       │      │      │  
Row 5  ⊞  ──  ⊞  ──  ⊞     GP7
       │      │      │  
Row 6     ⊞  ──  ⊞         GP8 (Thumbs)
       │      │      │  
      GP12   GP13   GP14
```

**Note:** Right half columns are physically 0-2 but electrically mapped as firmware columns 3-5.

**Detailed Connections:**
```
Row 0: GP2  → All switches in top row
Row 1: GP3  → All switches in second row  
Row 2: GP4  → All switches in third row
Row 3: GP5  → All switches in fourth row
Row 4: GP6  → All switches in fifth row
Row 5: GP7  → All switches in bottom row
Row 6: GP8  → All thumb cluster switches

Col 0: GP12 → All switches in leftmost column (right half)
Col 1: GP13 → All switches in middle column (right half)  
Col 2: GP14 → All switches in rightmost column (right half)
```

### 🔧 Critical Configuration

**Hand Detection (Essential!):**
```
GP16 ────  (Leave unconnected/floating)
    
No connection to GND tells firmware
this is the RIGHT/SLAVE half
```

### 🖲️ PMW3360 Trackball Sensor

**SPI Interface Wiring:**
```
PMW3360 Module     Raspberry Pi Pico
┌─────────────┐   ┌─────────────────┐
│ VCC (3.3V)  │◄──│ 3.3V (from TRRS)│
│ GND         │◄──│ GND             │
│ CS          │◄──│ GP17            │
│ SCK         │◄──│ GP18            │
│ MOSI        │◄──│ GP19            │
│ MISO        │──►│ GP20            │
│ Motion      │──►│ GP23 (optional) │
│ Reset       │◄──│ 3.3V + 10kΩ res │
└─────────────┘   └─────────────────┘
```

**Physical Mounting:**
- Mount sensor on underside of PCB
- Ensure proper alignment with trackball
- Use adequate clearance for ball movement
- Clean lens before final assembly

### 🎛️ Rotary Encoder

**Quadrature Encoder Wiring:**
```
Encoder            Raspberry Pi Pico
┌─────────────┐   ┌─────────────────┐
│ A Phase     │◄──│ GP21            │
│ B Phase     │◄──│ GP22            │
│ Common      │◄──│ GND             │
│ Switch      │◄──│ GP24 (optional) │
│ Switch GND  │◄──│ GND             │
└─────────────┘   └─────────────────┘
```

**Encoder Types Supported:**
- EC11 rotary encoder (most common)
- 24-step resolution (configurable in firmware)
- Optional push-button functionality

---

## ⚡ Critical Assembly Guidelines

### 🔍 Pre-Assembly Inspection

**Component Verification:**
- [ ] 2× Raspberry Pi Pico controllers
- [ ] 1× PMW3360 trackball sensor module  
- [ ] 1× Rotary encoder (EC11 compatible)
- [ ] 42× MX-compatible switches
- [ ] 42× 1N4148 diodes
- [ ] 2× TRRS jacks (3.5mm, 4-conductor)
- [ ] 1× USB-C connector/breakout
- [ ] TRRS cable (4-conductor)
- [ ] Wiring supplies (28-30 AWG wire recommended)

### 🔧 Diode Installation

**Critical Polarity Requirements:**
```
COL2ROW Configuration:

Row ←─┤|──── Switch ────← Column
       ▲
   Diode band (cathode)
   points toward ROW

Correct:   Row ←─┤|──── Column
Incorrect: Row ─►|├──── Column
```

**Installation Tips:**
- Install diodes before switches for easier access
- Use consistent orientation across entire build
- Double-check polarity before soldering
- Trim leads after soldering to prevent shorts

### 🔌 TRRS System Requirements

**Cable Specifications:**
- **Type**: TRRS (4-conductor) - not TRS (3-conductor)
- **Length**: < 1 meter recommended for signal integrity
- **Quality**: Shielded cable preferred
- **Connectors**: 3.5mm TRRS plugs, gold-plated preferred

**Jack Installation:**
```
TRRS Jack Pinout (looking at solder side):
    
    Sleeve ○ ○ Ring 2
    Ring 1 ○ ○ Tip
    
Mount securely to PCB with mechanical support
Test continuity before final assembly
```

**Signal Integrity:**
- Keep TRRS wiring away from switching matrix
- Use twisted pairs for power and ground
- Avoid running parallel to high-frequency signals
- Test with multimeter before power-on

### ⚙️ Hand Detection System

**Critical Configuration:**

| Half | GP16 Connection | Firmware Detection |
|------|----------------|-------------------|
| Left (Master) | GP16 → GND | `isLeftHand = true` |
| Right (Slave) | GP16 floating | `isLeftHand = false` |

**Common Mistakes:**
- ❌ Both halves connected to GND
- ❌ Both halves floating  
- ❌ Wrong half connected to GND
- ✅ Only left half GP16 → GND

### 🔌 Power Distribution

**Power Flow Architecture:**
```
USB-C ──► Left Pico ──TRRS──► Right Pico ──► Peripherals
        │                   │
        └► Left Matrix      └► Right Matrix + PMW3360 + Encoder
```

**Current Requirements:**
- Left half: ~50mA (matrix only)
- Right half: ~80mA (matrix + PMW3360 + encoder)
- Total: ~130mA (well within USB 500mA limit)

**Safety Checks:**
- Verify 3.3V on right half before connecting peripherals
- Check ground continuity between halves
- Monitor current draw during initial testing
- Use multimeter to verify voltages before power-on

---

## 🔧 Assembly & Testing Tips

### 📋 Pre-Assembly Checklist

**Workspace Preparation:**
- [ ] Clean, well-lit workspace
- [ ] ESD protection (wrist strap recommended)
- [ ] Organized component storage
- [ ] Soldering station with temperature control
- [ ] Flux, solder wick, multimeter ready

**Component Organization:**
- [ ] Diodes sorted and polarity-marked
- [ ] Wires pre-cut and labeled
- [ ] Switches tested and organized
- [ ] All pin assignments printed/visible

### 🔬 Step-by-Step Testing

**Phase 1: Power System Test**
1. Solder TRRS jacks and hand detection pins
2. Connect USB to left half only
3. Verify 3.3V on left half test points
4. Connect TRRS cable
5. Verify 3.3V and GND on right half
6. Test hand detection (flash test firmware)

**Phase 2: Matrix Testing**
1. Install diodes (verify polarity!)
2. Solder row and column connections
3. Test matrix continuity with multimeter
4. Install switches gradually, testing each row
5. Verify key registration with QMK testing tools

**Phase 3: Peripheral Integration**
1. Install PMW3360 sensor (right half)
2. Test SPI communication and tracking
3. Install rotary encoder
4. Test encoder rotation and button (if present)
5. Full system integration test

### 🔍 Testing Tools & Methods

**Hardware Testing:**
```bash
# QMK testing mode (if available)
qmk console
# Enable matrix debug output
# Watch for key press/release events
```

**Multimeter Tests:**
- Continuity: All GND connections
- Voltage: 3.3V rails on both halves  
- Resistance: Matrix paths when keys pressed
- Isolation: No shorts between adjacent pins

**Software Testing:**
- Key tester websites
- QMK Configurator test mode
- Vial real-time visualization
- Custom debugging firmware

### 🐛 Troubleshooting Guide

#### No Communication Between Halves

**Symptoms:**
- Right half not responding
- Only left half keys work
- No power to right half

**Diagnostic Steps:**
1. **Power Check**: Verify 3.3V on right half
   ```
   Multimeter DC voltage mode:
   Red probe → Right Pico 3.3V pin
   Black probe → Right Pico GND pin
   Expected: ~3.3V
   ```

2. **TRRS Cable Test**: Check all 4 conductors
   ```
   Multimeter continuity mode:
   Test each TRRS connection end-to-end
   Tip, Ring1, Ring2, Sleeve should all beep
   ```

3. **Hand Detection Verification**:
   ```
   Left half: GP16 should read 0V (connected to GND)
   Right half: GP16 should read 3.3V (floating, pulled up)
   ```

**Common Solutions:**
- Replace TRRS cable
- Re-solder TRRS jack connections
- Verify hand detection pin wiring
- Check for cold solder joints

#### Matrix Issues

**Symptoms:**
- Some keys not registering
- Ghost typing (wrong keys triggered)
- Inconsistent key response

**Diagnostic Steps:**
1. **Diode Check**: Verify polarity and continuity
2. **Row/Column Test**: Use multimeter to trace paths
3. **Switch Test**: Verify mechanical switch operation
4. **Firmware Debug**: Enable matrix debugging output

**Common Solutions:**
- Re-orient incorrectly installed diodes
- Re-flow cold solder joints
- Replace defective switches
- Check for wire breaks

#### PMW3360 Trackball Issues

**Symptoms:**
- No cursor movement
- Erratic tracking
- Sensor not detected

**Diagnostic Steps:**
1. **Power Verification**: 3.3V to sensor VCC
2. **SPI Communication**: Check CS, SCK, MOSI, MISO connections
3. **Physical Alignment**: Sensor position relative to ball
4. **Lens Cleaning**: Remove dust/debris from optical path

**Common Solutions:**
- Re-solder SPI connections
- Adjust sensor mounting height
- Clean trackball and lens
- Verify firmware SPI configuration

#### Encoder Problems

**Symptoms:**
- No scroll wheel function
- Reversed scroll direction
- Encoder button not working

**Diagnostic Steps:**
1. **Connection Verification**: A, B, Common pins
2. **Quadrature Testing**: Rotate and check voltage changes
3. **Button Testing**: Push and check switch continuity
4. **Firmware Configuration**: Verify encoder pin assignments

**Common Solutions:**
- Re-solder encoder connections
- Swap A and B pins if direction is wrong
- Replace encoder if mechanically defective
- Update firmware encoder configuration

---

## 📊 Pin Assignment Summary

### Complete Pin Mapping Table

| Function | Left Half | Right Half | Notes |
|----------|-----------|------------|-------|
| **Power & Communication** |
| USB Power | Native USB | - | Master only |
| TRRS Serial | GP1 | GP1 | Bidirectional |
| Hand Detection | GP16 → GND | GP16 (float) | Critical! |
| Status LED | GP25 | - | Optional |
| **Matrix (Rows)** |
| Row 0 | GP2 | GP2 | Shared names |
| Row 1 | GP3 | GP3 | Shared names |
| Row 2 | GP4 | GP4 | Shared names |
| Row 3 | GP5 | GP5 | Shared names |
| Row 4 | GP6 | GP6 | Shared names |
| Row 5 | GP7 | GP7 | Shared names |
| Row 6 (Thumbs) | GP8 | GP8 | Shared names |
| **Matrix (Columns)** |
| Column 0 | GP9 | GP12 | Local numbering |
| Column 1 | GP10 | GP13 | Local numbering |
| Column 2 | GP11 | GP14 | Local numbering |
| **Trackball (SPI)** |
| CS (Chip Select) | - | GP17 | SPI control |
| SCK (Serial Clock) | - | GP18 | SPI clock |
| MOSI (Data Out) | - | GP19 | SPI data → sensor |
| MISO (Data In) | - | GP20 | SPI data ← sensor |
| Motion Interrupt | - | GP23 | Optional |
| **Encoder** |
| A Phase | - | GP21 | Quadrature |
| B Phase | - | GP22 | Quadrature |
| Switch | - | GP24 | Optional push |

### Firmware Configuration Cross-Reference

**Config.h Verification:**
```c
// Matrix configuration
#define MATRIX_ROW_PINS { GP2, GP3, GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP9, GP10, GP11, GP12, GP13, GP14 }
#define DIODE_DIRECTION COL2ROW

// Split configuration  
#define SPLIT_HAND_PIN GP16
#define SPLIT_HAND_PIN_LOW_IS_LEFT  // GP16→GND = Left
#define SOFT_SERIAL_PIN GP1

// PMW3360 configuration
#define PMW3360_CS_PIN GP17
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19  
#define SPI_MISO_PIN GP20

// Encoder configuration
#define ENCODERS_PAD_A { GP21 }
#define ENCODERS_PAD_B { GP22 }
```

**Matrix.c Logic:**
```c
// Left half: scan columns 0-2 (GP9-GP11)
if (isLeftHand) {
    col_start = 0;
    col_end = MATRIX_COLS / 2;  // Columns 0-2
}
// Right half: scan columns 3-5 (GP12-GP14) 
else {
    col_start = MATRIX_COLS / 2;
    col_end = MATRIX_COLS;      // Columns 3-5
}
```

---

## 🎯 Final Assembly Verification

### Pre-Power Checklist

- [ ] All diodes installed with correct polarity (COL2ROW)
- [ ] Matrix row/column connections verified with multimeter
- [ ] TRRS jacks securely mounted and all 4 conductors connected
- [ ] Hand detection: Left GP16→GND, Right GP16 floating
- [ ] PMW3360 SPI connections verified (right half only)
- [ ] Encoder A/B/GND connections verified (right half only)
- [ ] No shorts between adjacent pins
- [ ] All ground connections solid and continuous

### First Power-On Procedure

1. **Left Half Only**: Connect USB, verify power LED and basic function
2. **TRRS Connection**: Connect cable, verify 3.3V on right half
3. **Split Communication**: Test basic key matrix on both halves  
4. **Peripheral Test**: Verify trackball tracking and encoder rotation
5. **Full Integration**: Test all features with final firmware

### Quality Assurance

- [ ] All 42 keys register correctly
- [ ] Trackball movement smooth in all directions
- [ ] Encoder rotation registers properly (both directions)
- [ ] Split communication stable (no dropouts)
- [ ] No ghost keys or matrix issues
- [ ] Firmware uploads and configures correctly
- [ ] VIAL/VIA configuration loads properly

**Success Criteria**: Both halves function independently and together, all 42 keys register, trackball tracks smoothly, encoder scrolls properly, and the system is stable under normal use conditions.

---

*This completes the comprehensive wiring guide for the RattusBoard split keyboard. For additional support, refer to the main [README.md](README.md) or open an issue in the project repository.*