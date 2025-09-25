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
│  MATRIX 4×6         │              │  MATRIX 4×6         │
│  Cols: GP9-GP14     │              │  Cols: GP15-GP20    │
│  Rows: GP2-GP5      │              │  Rows: GP2-GP5      │
│                     │              │                     │
│  Split Pin: GP21→GND│              │  Split Pin: GP21    │
│  TRRS: GP1          │              │  TRRS: GP1          │
│                     │              │                     │
│                     │              │  [PMW3360 SENSOR]   │
│                     │              │  SPI: GP22-GP25     │
│                     │              │                     │
│                     │              │  [ROTARY ENCODER]   │
│                     │              │  Pins: GP26-GP27    │
└─────────────────────┘              └─────────────────────┘
        MASTER                              SLAVE
     (USB Connected)                    (TRRS Powered)
```

**NEW MATRIX DESIGN:**
- **4×6 Matrix per half** - 3 main rows + 1 thumb row
- **42 Total Keys** - 21 per half  
- **Thumb Cluster**: Left (cols 3,4,5), Right (cols 0,1,2)
- **TRRS Communication** - Only for coordination between halves via GP1

**Signal Flow:**
```
Computer ──USB-C──► Left Pico ──TRRS──► Right Pico
                        │                    │
                   Matrix 4×6           Matrix 4×6
                 (Independent)        (Independent)
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

**New 4×6 Matrix Layout (Left Half):**
```
    Switch Matrix Layout (Left Half)
    
    Col 0   Col 1   Col 2   Col 3   Col 4   Col 5
Row 0  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞     GP2
       │      │      │      │      │      │  
Row 1  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞     GP3
       │      │      │      │      │      │  
Row 2  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞     GP4
       │      │      │      │      │      │  
Row 3  ---    ---    ---    ⊞  ──  ⊞  ──  ⊞     GP5 (Thumb cluster)
       │      │      │      │      │      │  
      GP9    GP10   GP11   GP12   GP13   GP14
```

**Detailed Connections:**
```
Row 0: GP2  → All switches in top row (K00-K05)
Row 1: GP3  → All switches in second row (K10-K15)
Row 2: GP4  → All switches in third row (K20-K25)
Row 3: GP5  → Thumb cluster switches (K33, K34, K35)

Col 0: GP9  → All switches in column 0 (K00, K10, K20)
Col 1: GP10 → All switches in column 1 (K01, K11, K21)
Col 2: GP11 → All switches in column 2 (K02, K12, K22)
Col 3: GP12 → All switches in column 3 (K03, K13, K23, K33)
Col 4: GP13 → All switches in column 4 (K04, K14, K24, K34)
```

### 🔧 Critical Configuration

**Hand Detection (Essential!):**
```
GP21 ──┐
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

**New 4×6 Matrix Layout (Right Half):**
```
    Switch Matrix Layout (Right Half)
    
    Col 0   Col 1   Col 2   Col 3   Col 4   Col 5
Row 0  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞     GP2
       │      │      │      │      │      │  
Row 1  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞     GP3
       │      │      │      │      │      │  
Row 2  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞  ──  ⊞     GP4
       │      │      │      │      │      │  
Row 3  ⊞  ──  ⊞  ──  ⊞  ──  ---    ---    ---    GP5 (Thumb cluster)
       │      │      │      │      │      │  
      GP15   GP16   GP17   GP18   GP19   GP20
```

**Detailed Connections:**
```
Row 0: GP2  → All switches in top row (K06-K0B)
Row 1: GP3  → All switches in second row (K16-K1B)
Row 2: GP4  → All switches in third row (K26-K2B)
Row 3: GP5  → Thumb cluster switches (K30, K31, K32)

Col 0: GP15 → All switches in column 0 (K06, K16, K26, K30)
Col 1: GP16 → All switches in column 1 (K07, K17, K27, K31)
Col 2: GP17 → All switches in column 2 (K08, K18, K28, K32)
Col 3: GP18 → All switches in column 3 (K09, K19, K29)
Col 4: GP19 → All switches in column 4 (K0A, K1A, K2A)
Col 5: GP20 → All switches in column 5 (K0B, K1B, K2B)

```

### 🔧 Critical Configuration

**Hand Detection (Essential!):**
```
GP21 ────  (Leave unconnected/floating)
    
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
│ CS          │◄──│ GP22            │
│ SCK         │◄──│ GP23            │
│ MOSI        │◄──│ GP24            │
│ MISO        │──►│ GP25            │
│ Motion      │──►│ GP28 (optional) │
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
│ A Phase     │◄──│ GP26            │
│ B Phase     │◄──│ GP27            │
│ Common      │◄──│ GND             │
│ Switch      │◄──│ GP28 (optional) │
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
| Hand Detection | GP21 → GND | GP21 (float) | Critical! |
| Status LED | GP28 | - | Optional |
| **Matrix (Rows) - NEW 4×6 LAYOUT** |
| Row 0 | GP2 | GP2 | **Independent pins** |
| Row 1 | GP3 | GP3 | **Independent pins** |
| Row 2 | GP4 | GP4 | **Independent pins** |
| Row 3 (Thumbs) | GP5 | GP5 | **Independent pins** |
| **Matrix (Columns) - NEW 4×6 LAYOUT** |
| Column 0 | GP9 | GP15 | **Fully independent** |
| Column 1 | GP10 | GP16 | **Fully independent** |
| Column 2 | GP11 | GP17 | **Fully independent** |
| Column 3 | GP12 | GP18 | **Fully independent** |
| Column 4 | GP13 | GP19 | **Fully independent** |
| Column 5 | GP14 | GP20 | **Fully independent** |
| **Trackball (SPI)** |
| CS (Chip Select) | - | GP22 | SPI control |
| SCK (Serial Clock) | - | GP23 | SPI clock |
| MOSI (Data Out) | - | GP24 | SPI data → sensor |
| MISO (Data In) | - | GP25 | SPI data ← sensor |
| Motion Interrupt | - | GP29 | Optional |
| **Encoder** |
| A Phase | - | GP26 | Quadrature |
| B Phase | - | GP27 | Quadrature |
| Switch | - | GP28 | Optional push |

### Firmware Configuration Cross-Reference

**Config.h Verification:**
```c
// Matrix configuration - NEW 4x6 LAYOUT
#define MATRIX_ROWS 4
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { GP2, GP3, GP4, GP5 }
#define MATRIX_COL_PINS { GP15, GP16, GP17, GP9, GP10, GP11 }
#define DIODE_DIRECTION COL2ROW

// Split configuration  
#define SPLIT_HAND_PIN GP21
#define SPLIT_HAND_PIN_LOW_IS_LEFT  // GP21→GND = Left
#define SOFT_SERIAL_PIN GP1

// PMW3360 configuration (right half only)
#define PMW33XX_CS_PIN GP22
#define SPI_SCK_PIN GP23
#define SPI_MOSI_PIN GP24  
#define SPI_MISO_PIN GP25

// Encoder configuration (right half only)
#define ENCODERS_PAD_A { GP26 }
#define ENCODERS_PAD_B { GP27 }
```

**Matrix.c Logic:**
```c
// Each half scans its own 4x6 matrix
// New layout: 3 main rows + 1 thumb row
// Thumb clusters: Left (cols 3,4,5), Right (cols 0,1,2)
for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    // Scan all 6 columns on this half
}
```

**Key Changes:**
- **MATRIX_ROWS = 4** (3 main + 1 thumb row)
- **MATRIX_COLS = 6** (6 columns per half)
- **New thumb cluster arrangement** - asymmetric placement
- **Simplified scanning** - no column offset logic needed
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
