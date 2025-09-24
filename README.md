# 🐭 RattusBoard

*A premium QMK-powered split ergonomic keyboard with integrated trackball and encoder*

[![QMK Firmware](https://img.shields.io/badge/QMK-Firmware-blue.svg)](https://qmk.fm/)
[![Vial Support](https://img.shields.io/badge/Vial-Supported-green.svg)](https://get.vial.today/)
[![License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](LICENSE)

---

## 🌟 Overview

RattusBoard is a cutting-edge split ergonomic keyboard designed for productivity enthusiasts and professionals who demand precision, comfort, and customization. Built on the robust QMK firmware foundation, it combines the beloved Corne layout with modern features including an integrated trackball and rotary encoder.

### ✨ Key Features

- **🎯 Ergonomic Split Design**: Based on the popular Corne layout for optimal hand positioning
- **🖲️ Integrated Trackball**: PMW3360 sensor for precise cursor control without leaving the keyboard
- **🎛️ Rotary Encoder**: Smooth scrolling and customizable input functions
- **🚀 QMK Firmware**: Full programmability with layers, macros, and advanced features
- **⚡ Vial Support**: Real-time keymap editing without flashing firmware
- **🔧 Raspberry Pi Pico**: Powerful RP2040 microcontroller for reliable performance
- **🎨 Customizable**: Open-source design encouraging modifications and improvements

---

## 📋 Hardware Specifications

### Core Components

| Component | Specification | Purpose |
|-----------|---------------|---------|
| **Microcontroller** | Raspberry Pi Pico (RP2040) | Main processing unit |
| **Layout** | Corne-inspired split (3x6+3) | Ergonomic key arrangement |
| **Trackball Sensor** | PMW3360 | High-precision optical tracking |
| **Encoder** | Rotary encoder | Scroll wheel and navigation |
| **Switches** | MX-compatible | Hot-swappable key switches |
| **Connectivity** | USB-C / TRRS | Wired connection between halves |

### Technical Specifications

- ⚡ **MCU**: RP2040 dual-core ARM Cortex-M0+ @ 133MHz
- 💾 **Memory**: 264KB SRAM, 2MB Flash
- 🔌 **Connection**: USB-C for host, TRRS for split communication
- 📊 **Polling Rate**: 1000Hz
- 🎯 **Trackball DPI**: Up to 12,000 (configurable)
- 🔄 **Encoder Resolution**: 24 steps per rotation

---

## 🛠️ Build Guide

### Required Tools & Materials

#### Tools Needed
- [ ] Soldering iron (temperature controlled recommended)
- [ ] Solder (rosin-core, 0.6-0.8mm)
- [ ] Flux
- [ ] Desoldering braid/pump
- [ ] Wire strippers
- [ ] Small Phillips screwdriver
- [ ] Multimeter (for troubleshooting)

#### Components Required
- [ ] 2x Raspberry Pi Pico microcontrollers
- [ ] 1x PMW3360 trackball sensor module
- [ ] 1x Rotary encoder (EC11 compatible)
- [ ] 42x MX-compatible switches
- [ ] 42x 1N4148 diodes
- [ ] 2x TRRS jacks (3.5mm)
- [ ] 1x USB-C connector
- [ ] Resistors and capacitors (as per schematic)
- [ ] Wire (28-30 AWG recommended)

### 🔌 Wiring Guide



This section provides essential wiring information for the RattusBoard split keyboard. For comprehensive assembly instructions, troubleshooting, and detailed diagrams, see the **[detailed wiring guide](HALVES_WIRING.md)**.


```
Left Half (Master)              Right Half (Slave)
┌─────────────────┐            ┌─────────────────┐
│  [USB-C INPUT]  │            │                 │
│ Raspberry Pi    │◄── TRRS ──►│ Raspberry Pi    │
│ Pico            │            │ Pico            │
│                 │            │                 │
│ INDEPENDENT 3×7 │            │ INDEPENDENT 3×7 │
│ GP16 → GND      │            │ GP16 (floating) │
└─────────────────┘            │ [PMW3360]       │
                               │ [Encoder]       │
                               └─────────────────┘
```

#### 📋 Complete Pin Assignment Reference

| Component | Function | Left Half | Right Half | Notes |
|-----------|----------|-----------|------------|-------|
| **Matrix Rows** | Key scanning | GP2-GP8 | GP2-GP8 | **INDEPENDENT** - No shared pins |
| **Matrix Cols** | Key scanning | GP9-GP11 | GP12-GP14 | **FULLY INDEPENDENT** matrices |
| **Split Comm** | UART Serial | GP0/GP1 | GP0/GP1 | Full-duplex serial over TRRS |
| **Hand Detection** | Split ID | GP16→GND | GP16 (float) | **Critical for auto-detection** |
| **USB Power** | Host connection | Native USB-C | - | Left half only (master) |
| **PMW3360 CS** | SPI Chip Select | - | GP17 | Trackball sensor control |
| **PMW3360 SCK** | SPI Clock | - | GP18 | High-speed SPI clock |
| **PMW3360 MOSI** | SPI Data Out | - | GP19 | Data to sensor |
| **PMW3360 MISO** | SPI Data In | - | GP20 | Data from sensor |
| **PMW3360 Motion** | Interrupt | - | GP23 (opt) | Motion detection |
| **Encoder A** | Quadrature | - | GP21 | Rotary encoder phase A |
| **Encoder B** | Quadrature | - | GP22 | Rotary encoder phase B |
| **Boot LED** | System | GP25 | GP25 | RP2040 onboard LED |

### 🔌 Enhanced Wiring Diagram

```
         RattusBoard Split Keyboard Architecture
         =======================================

Left Half (Master)                    Right Half (Slave)
┌─────────────────────┐               ┌─────────────────────┐
│  [USB-C INPUT]      │               │                     │
│  Raspberry Pi Pico  │◄──── TRRS ────┤  Raspberry Pi Pico  │
│  RP2040 Master      │               │  RP2040 Slave       │
│                     │               │                     │
│  Matrix: 3×7        │               │  Matrix: 3×7        │
│  ┌─────────────┐    │               │  ┌─────────────┐    │
│  │ GP2-GP8     │    │               │  │ GP2-GP8     │    │
│  │ (Rows)      │    │               │  │ (Rows)      │    │
│  │ GP9-GP11    │    │               │  │ GP12-GP14   │    │
│  │ (Cols)      │    │               │  │ (Cols)      │    │  
│  └─────────────┘    │               │  └─────────────┘    │
│                     │               │                     │
│  GP16 → GND (Left)  │               │  GP16 (Float/Right) │
│  GP0/GP1 (UART)    │               │  GP0/GP1 (UART)    │
└─────────────────────┘               │                     │
                                      │  🖲️ PMW3360 Module  │
                                      │  ┌─────────────┐    │
                                      │  │ GP17 (CS)   │    │
                                      │  │ GP18 (SCK)  │    │
                                      │  │ GP19 (MOSI) │    │
                                      │  │ GP20 (MISO) │    │
                                      │  │ GP23 (MOT)  │    │
                                      │  └─────────────┘    │
                                      │                     │
                                      │  🎛️ Rotary Encoder  │
                                      │  ┌─────────────┐    │
                                      │  │ GP21 (A)    │    │
                                      │  │ GP22 (B)    │    │
                                      │  │ [GP24 (SW)] │    │
                                      │  └─────────────┘    │
                                      └─────────────────────┘

TRRS Cable Wiring:
┌─────────────────────────────────────────────────────────┐
│ Tip    (T): GND        Ring 1 (R1): UART TX/RX         │
│ Ring 2 (R2): 3.3V      Sleeve (S): UART RX/TX          │
└─────────────────────────────────────────────────────────┘
```

### 🎯 Feature Implementation Status

| Feature | Status | Implementation | Notes |
|---------|--------|----------------|-------|
| **Split Keyboard** | ✅ Complete | UART Serial | Hardware auto-detection |
| **PMW3360 Trackball** | ✅ Complete | SPI Driver | 1600 DPI, configurable |
| **Rotary Encoder** | ✅ Complete | Quadrature | 4 steps/detent, per-layer |
| **VIA/VIAL Support** | ✅ Complete | JSON Config | Real-time keymap editing |
| **4-Layer Layout** | ✅ Complete | QMK Layers | Base, Lower, Raise, Adjust |
| **Trackball Controls** | ✅ Complete | Custom Keys | DPI adjust, scroll toggle |
| **Encoder Functions** | ✅ Complete | Per-Layer | Scroll, volume, brightness |
| **Custom Matrix** | ✅ Complete | Split-aware | Independent matrices |


#### 🔧 Quick Assembly Steps

1. **Install diodes** with correct polarity (band toward row)
2. **Wire matrix** according to pin assignments above  
3. **Configure hand detection** (GP16→GND on left only)
4. **Install TRRS jacks** and verify cable connectivity
5. **Add peripherals** (trackball, encoder on right half)
6. **Test thoroughly** before final assembly

---

## 🎹 Keymap Overview

RattusBoard features a 4-layer layout adapted from the popular Corne keyboard, optimized for productivity and comfort with integrated trackball and encoder functionality.

### 📊 Layer Architecture

```
Layer Stack:
┌─────────────┐
│   ADJUST    │ ← System, Mouse, Reset
├─────────────┤
│    RAISE    │ ← Symbols, Media Controls  
├─────────────┤
│    LOWER    │ ← Numbers, F-keys, Navigation
├─────────────┤
│    BASE     │ ← QWERTY Layout (Default)
└─────────────┘
```

### 🗝️ Layer Details

#### **Layer 0: BASE (QWERTY)**
```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  Q  │  W  │  E  │  R  │  T  │     │   │     │  Y  │  U  │  I  │  O  │  P  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  A  │  S  │  D  │  F  │  G  │     │   │     │  H  │  J  │  K  │  L  │  ;  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  Z  │  X  │  C  │  V  │  B  │     │   │     │  N  │  M  │  ,  │  .  │  /  │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ SPC │LOWER│   │RAISE│ ENT │ ALT │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
                                          🖲️     🎛️
                                      Trackball Encoder
```
**Trackball:** Cursor movement, click & drag  
**Encoder:** Vertical scroll (↕️)

#### **Layer 1: LOWER (Numbers & Navigation)**
```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  1  │  2  │  3  │  4  │  5  │  6  │   │  6  │  7  │  8  │  9  │  0  │BSPC │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │   │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│F11  │F12  │TB_TO│DPI- │DPI+ │     │   │     │ ←   │ ↓   │ ↑   │ →   │     │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ SPC │ --- │   │ADJST│ ENT │ ALT │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```
**Trackball:** TB_TOG = Toggle scroll mode, DPI± = Sensitivity  
**Encoder:** Volume control (🔊)

#### **Layer 2: RAISE (Symbols & Media)**
```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  !  │  @  │  #  │  $  │  %  │  ^  │   │  ^  │  &  │  *  │  (  │  )  │BSPC │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  -  │  =  │  [  │  ]  │  \  │  '  │   │  '  │  ;  │  ,  │  .  │  /  │  `  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  _  │  +  │  {  │  }  │  |  │MUTE │   │MUTE │VOL- │VOL+ │PLAY │NEXT │     │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ SPC │ADJST│   │ --- │ ENT │ ALT │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```
**Trackball:** Cursor movement  
**Encoder:** Horizontal scroll (↔️)

#### **Layer 3: ADJUST (System & Mouse)**
```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│RESET│     │     │     │     │     │   │     │     │     │     │     │RESET│
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │MS_L │   │MS_L │MS_D │MS_U │MS_R │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │BTN1 │   │BTN1 │BTN2 │BTN3 │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ SPC │ --- │   │ --- │ ENT │ ALT │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘  
```
**Trackball:** Mouse emulation (for backup/precision)  
**Encoder:** Brightness control (🔆)

### 🎛️ Encoder Functions by Layer

| Layer | Function | CCW (↺) | CW (↻) |
|-------|----------|---------|--------|
| **BASE** | Scroll | Scroll Up | Scroll Down |
| **LOWER** | Audio | Volume Down | Volume Up |
| **RAISE** | Scroll | Scroll Left | Scroll Right |
| **ADJUST** | Display | Brightness Down | Brightness Up |

### 🖲️ Trackball Modes

| Mode | Activation | Function | Use Case |
|------|------------|----------|----------|
| **Cursor** | Default | Mouse movement | Navigation, selection |
| **Scroll** | TB_TOG key | Scroll wheel | Document scrolling |
| **DPI Low** | TB_DPI_DN | Precision mode | Fine adjustments |
| **DPI High** | TB_DPI_UP | Speed mode | Quick movements |

---

## 📸 Visual Preview

> **Coming Soon!** 📷  
> This section will showcase:
> - ✨ Assembled keyboard glamour shots
> - 🔍 Close-up details of trackball integration  
> - 🎛️ Rotary encoder implementation
> - 📐 Size comparison with standard keyboards
> - 🌈 RGB lighting effects (if implemented)
> - 🎨 Various keycap and switch combinations

*Please share your RattusBoard builds! Photos welcome for this gallery.*

### 🎯 Build Showcase Categories
- **Clean Builds**: Minimalist, professional setups
- **RGB Builds**: Colorful, illuminated configurations  
- **Custom Builds**: Unique modifications and improvements
- **Work Setups**: Professional desk integrations
- **Gaming Rigs**: Performance-focused configurations

**📧 Submit your photos:** Create an issue with the "showcase" label or PR with images!

**For complete step-by-step instructions, wiring diagrams, troubleshooting, and testing procedures, refer to [HALVES_WIRING.md](HALVES_WIRING.md).**

### 🧪 Testing the Firmware

To verify that the firmware compiles correctly, you can test it without actual hardware:

```bash
# Install QMK CLI (if not already installed)
pip3 install qmk

# Setup QMK environment
qmk setup

# Copy the RattusBoard files to your QMK installation
cp -r keyboards/rattusboard ~/.local/share/qmk/keyboards/

# Test compilation
qmk compile -kb rattusboard -km default

# The compilation should complete without errors and produce a .uf2 file
```

**Expected Output:** The compilation should complete successfully and generate `rattusboard_default.uf2` ready for flashing to the Raspberry Pi Pico.

### 📚 Firmware Structure

```
keyboards/rattusboard/
├── config.h              # Hardware configuration and pin assignments
├── rules.mk              # Build configuration and feature flags
├── info.json             # Physical layout and keyboard metadata
├── vial.json             # VIAL compatibility configuration
├── rattusboard.h         # Layout definitions and custom keycodes
├── rattusboard.c         # Main keyboard implementation
├── matrix.c              # Custom matrix scanning for split keyboard
├── halconf.h             # HAL configuration for RP2040
├── mcuconf.h             # MCU configuration for SPI support
└── keymaps/
    └── default/
        └── keymap.c       # Default 4-layer keymap
```

### 🎯 Key Features Implemented

- ✅ **Split Keyboard Support**: Full split keyboard functionality with TRRS communication
- ✅ **PMW3360 Trackball**: High-precision optical sensor with configurable DPI
- ✅ **Rotary Encoder**: Configured as scroll wheel with per-layer functions
- ✅ **VIAL Compatibility**: Real-time keymap editing support
- ✅ **Custom Matrix**: 6x7 matrix optimized for Corne-style layout
- ✅ **RP2040 Support**: Full Raspberry Pi Pico compatibility
- ✅ **4-Layer Layout**: Base, Lower, Raise, and Adjust layers
- ✅ **Trackball Controls**: DPI adjustment and scroll mode toggle

### Assembly Steps

#### Phase 1: PCB Preparation
1. **Inspect PCBs**: Check for any manufacturing defects
2. **Clean PCBs**: Remove any flux residue or debris
3. **Test Continuity**: Verify all traces are intact

#### Phase 2: Component Installation
1. **Diodes**: Solder all 1N4148 diodes (mind polarity!)
2. **Resistors**: Install pull-up resistors for I2C communication
3. **Capacitors**: Add decoupling capacitors near power pins
4. **TRRS Jacks**: Mount communication connectors
5. **USB-C**: Install on right half (master) only

#### Phase 3: Microcontroller Installation
1. **Socket Installation** (recommended): Install mill-max sockets
2. **Pico Mounting**: Carefully align and solder Raspberry Pi Picos
3. **Power Test**: Verify 3.3V and 5V rails

#### Phase 4: Sensor Integration
1. **PMW3360 Module**: Mount trackball sensor (check orientation)
2. **Encoder Installation**: Mount rotary encoder securely
3. **Wire Management**: Route wires cleanly to avoid interference

#### Phase 5: Final Assembly
1. **Switch Installation**: Insert and secure all key switches
2. **Keycap Installation**: Attach keycaps to switches
3. **Case Assembly**: Mount PCBs in cases (if using)
4. **Cable Connection**: Connect halves with TRRS cable

---

## 💻 Firmware Installation

### Prerequisites

#### Required Software
- [QMK Toolbox](https://github.com/qmk/qmk_toolbox) or  
- [QMK CLI](https://docs.qmk.fm/#/newbs_getting_started)
- [Vial](https://get.vial.today/) (for real-time keymap editing)

#### Development Environment Setup
```bash
# Install QMK CLI
pip3 install qmk

# Set up QMK environment  
qmk setup

# Copy RattusBoard keyboard files to QMK
cp -r keyboards/rattusboard ~/.local/share/qmk/keyboards/
```

### 📦 Firmware Download

#### Latest Release
[![Latest Release](https://img.shields.io/github/v/release/Rattus-ukrizovany/RattusBoard?include_prereleases&label=Latest%20Firmware)](https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest)

**Quick Download:**
- **[Download Latest Firmware (.uf2)](https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest/download/rattusboard_latest.uf2)** ⬇️
- **[All Releases & Versions](https://github.com/Rattus-ukrizovany/RattusBoard/releases)** 📋

#### Automated Builds
The firmware is automatically built and released using GitHub Actions:
- ✅ **On every release** - Tagged version with release assets
- ✅ **On main branch changes** - Development builds available as artifacts
- ✅ **On pull requests** - Testing builds for validation

#### 🔄 Split Keyboard Firmware Downloads
The RattusBoard uses a split keyboard design requiring separate firmware files for each half. Both sides use the **rp2040_pro_micro** MCU target (implemented via QMK's `rp2040_ce` converter for RP2040 Pro Micro compatible boards).

**Latest Build Artifacts:**
- **[Left Side Firmware](https://github.com/Rattus-ukrizovany/RattusBoard/actions/workflows/split-firmware-build.yml)** - `rattusboard_left-rp2040_pro_micro-firmware`
- **[Right Side Firmware](https://github.com/Rattus-ukrizovany/RattusBoard/actions/workflows/split-firmware-build.yml)** - `rattusboard_right-rp2040_pro_micro-firmware`

**How to Download:**
1. 🔗 **[Visit the Actions Page](https://github.com/Rattus-ukrizovany/RattusBoard/actions/workflows/split-firmware-build.yml)**
2. 📋 Click on the latest **successful** workflow run
3. 📦 Scroll down to **Artifacts** section
4. ⬇️ Download both:
   - `rattusboard_left-rp2040_pro_micro-firmware.uf2` (for left half)
   - `rattusboard_right-rp2040_pro_micro-firmware.uf2` (for right half)

**Important Notes:**
- 🎯 **Both files are required** - one for each half of the split keyboard
- ⚠️ **Flash the correct firmware to each side** - left firmware to left half, right firmware to right half
- 🔄 **Artifacts are available for 90 days** after each build
- 🏷️ **Release builds** permanently attach firmware files to GitHub releases
- 💡 **Technical Note**: Uses QMK's `rp2040_ce` converter for RP2040 Pro Micro compatible boards

#### What's Included
- **Full QMK firmware** with Vial support
- **4-layer default keymap** (Base, Lower, Raise, Adjust)
- **PMW3360 trackball support** with configurable DPI
- **Rotary encoder support** with per-layer functions
- **Split keyboard functionality** for both halves

### 📁 QMK Firmware Files

The RattusBoard firmware includes the following files located in `keyboards/rattusboard/`:

**Core Configuration:**
- `config.h` - Hardware configuration, pin assignments, and feature flags
- `rules.mk` - Build configuration and enabled features  
- `info.json` - Physical layout and keyboard metadata
- `vial.json` - VIAL compatibility configuration

**Implementation Files:**
- `rattusboard.h` - Keyboard layout definitions and custom keycodes
- `rattusboard.c` - Main keyboard implementation with trackball and encoder support
- `matrix.c` - Custom matrix scanning for split keyboard

**Default Keymap:**
- `keymaps/default/keymap.c` - Default 4-layer keymap with encoder scroll wheel support

### 🚀 Enhanced Flashing Guide

#### 📦 Quick Start (5 Minutes)

**What You Need:**
- 2× Raspberry Pi Pico microcontrollers
- 1× USB-C cable  
- Computer with web browser

**Step-by-Step:**

1. **📥 Download Firmware**
   ```
   Latest Release: rattusboard_default.uf2
   🔗 https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest
   ```

2. **🔌 Flash Left Half (Master)**
   - Hold **BOOTSEL** + Connect USB → Pico shows as **RPI-RP2** drive
   - Drag `rattusboard_default.uf2` to the drive
   - ✅ Pico reboots automatically with firmware

3. **🔌 Flash Right Half (Slave)**  
   - Repeat step 2 with second Pico
   - ✅ Same firmware works for both halves

4. **🔗 Connect & Test**
   - Connect halves with TRRS cable
   - Plug USB into **left half only**
   - ✅ Both halves should work!

#### 🛠️ Advanced Compilation

**Prerequisites:**
```bash
# Install QMK CLI
pip3 install qmk

# Setup QMK environment
qmk setup
```

**Build Custom Firmware:**
```bash
# Clone RattusBoard
git clone https://github.com/Rattus-ukrizovany/RattusBoard.git
cd RattusBoard

# Copy to QMK directory
cp -r keyboards/rattusboard ~/.local/share/qmk/keyboards/

# Compile with custom keymap
qmk compile -kb rattusboard -km default

# Output: rattusboard_default.uf2
```

**Flash Directly:**
```bash
# Flash while in bootloader mode
qmk flash -kb rattusboard -km default

# Or use QMK Toolbox GUI
```

#### 🔧 Troubleshooting Flash Issues

| Problem | Solution |
|---------|----------|
| **Pico not detected** | Try different USB cable, ensure BOOTSEL held during connection |
| **Drive disappears** | Normal behavior - Pico reboots after firmware flash |
| **No response** | Check TRRS cable, verify both halves flashed |
| **Keys not working** | Test with key tester website, check matrix wiring |
| **Trackball issues** | Verify SPI connections, clean sensor lens |
| **Encoder problems** | Check quadrature pins, test with encoder test |

#### ⚙️ Firmware Customization Options

**1. VIA/VIAL (Real-time editing)** ⭐
- Download **Vial** from [get.vial.today](https://get.vial.today)  
- Keyboard auto-detected with included `vial.json`
- Edit keymap, macros, encoder functions live

**2. QMK Configurator (Web-based)**
- Upload `keyboard.json` to [config.qmk.fm](https://config.qmk.fm)
- Design keymap visually
- Download compiled firmware

**3. Source Code (Advanced)**
- Modify `keymaps/default/keymap.c`
- Add custom functions in `rattusboard.c`
- Build with `qmk compile`

#### 🎯 Validation Checklist

After flashing, verify these features work:

- [ ] **All keys register** (use online key tester)
- [ ] **Split communication** (both halves respond)  
- [ ] **Layer switching** (LOWER/RAISE keys)
- [ ] **Trackball movement** (cursor moves smoothly)  
- [ ] **Trackball clicking** (left/right click works)
- [ ] **Encoder rotation** (scroll wheel functions)
- [ ] **Trackball toggle** (TB_TOG switches scroll mode)
- [ ] **DPI adjustment** (TB_DPI_UP/DN changes sensitivity)
- [ ] **Per-layer encoder** (different functions each layer)

**🎉 Success!** Your RattusBoard is ready for use!

### 🔧 Split Keyboard Configuration

The QMK firmware for RattusBoard is fully configured for split keyboard operation:

#### Firmware Compatibility ✅
- **Split Detection**: Hardware-based using GP16 pin (automatic hand detection)
- **Communication**: Serial communication via GP1 pin over TRRS cable
- **Power Management**: Master (left) powers slave (right) via TRRS Ring 2
- **Matrix Configuration**: Proper column offsets for split operation
- **Peripheral Support**: PMW3360 trackball and encoder on right half only

#### Key Configuration Parameters
```c
// Split keyboard settings (from config.h)
#define SPLIT_HAND_PIN GP16              // Hardware hand detection
#define SPLIT_HAND_PIN_LOW_IS_LEFT       // GP16→GND = left half
#define SOFT_SERIAL_PIN GP1              // TRRS serial communication
#define SPLIT_USB_DETECT                 // USB detection for master
#define SPLIT_KEYBOARD                   // Enable split functionality
```

#### No Additional Configuration Needed
The firmware works out-of-the-box with the split wiring described in [WIRING_GUIDE.md](WIRING_GUIDE.md). The same firmware binary is flashed to both halves - hardware pin configuration (GP16) automatically determines which half is which.

#### Firmware Implementation Details
- **Automatic Hand Detection**: The firmware reads GP16 at startup to determine left vs right half
- **Independent Matrix Scanning**: Each half scans its own complete 3x7 matrix independently
- **Serial Communication**: Both halves use GP1 for UART communication over TRRS cable
- **Power Management**: Left half supplies 3.3V to right half via TRRS Ring 2
- **Peripheral Handling**: PMW3360 and encoder are only active on the right half
- **No Shared Pins**: Each half is completely independent with dedicated row and column pins

#### Validation
Run these commands to verify your configuration:
```bash
# Copy keyboard files to QMK directory
cp -r keyboards/rattusboard ~/.local/share/qmk/keyboards/

# Validate configuration (warnings about deprecated options are normal)
qmk compile -kb rattusboard -km default --dry-run

# The firmware should compile successfully despite deprecation warnings
```

---

## 🎮 Vial Configuration

### Setting Up Vial

1. **Download Vial**: Get the latest version from [get.vial.today](https://get.vial.today/)
2. **Connect Keyboard**: Ensure RattusBoard is flashed with Vial-compatible firmware
3. **Auto-Detection**: Vial should automatically detect your keyboard

### Key Features in Vial

#### Layer Management
- **Multiple Layers**: Configure up to 16 layers
- **Layer Switching**: Momentary, toggle, or one-shot layer keys
- **Visual Feedback**: Real-time layer indication

#### Trackball Configuration
- **DPI Settings**: Adjust sensitivity for different tasks
- **Scroll Mode**: Toggle between cursor and scroll modes
- **Acceleration**: Configure movement curves

#### Encoder Functions
- **Per-Layer Settings**: Different functions on each layer
- **Common Uses**:
  - Volume control
  - Zoom in/out
  - Tab switching
  - Timeline scrubbing

#### Macro Programming
- **Text Macros**: Automate common phrases
- **Key Sequences**: Complex keystroke combinations
- **Timing Control**: Adjust delays between keystrokes

### Default Layout

```
Layer 0 (Base):
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  Q  │  W  │  E  │  R  │  T  │     │   │     │  Y  │  U  │  I  │  O  │  P  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  A  │  S  │  D  │  F  │  G  │     │   │     │  H  │  J  │  K  │  L  │  ;  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  Z  │  X  │  C  │  V  │  B  │     │   │     │  N  │  M  │  ,  │  .  │  /  │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ SPC │LOWER│   │RAISE│ ENT │ ALT │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
                                         Trackball  Encoder
```

---

## 📸 Gallery

> **Note**: Photos will be added here once provided. The gallery will showcase:
> - Assembled keyboard from multiple angles
> - Close-up shots of trackball and encoder
> - Lighting effects (if applicable)
> - Different switch and keycap combinations
> - Build process documentation

*📷 Photo gallery coming soon! Please provide images for this section.*

---

## 🔧 Troubleshooting

### Common Issues

#### Keyboard Not Detected
- **Check USB Connection**: Ensure cable is properly connected
- **Driver Issues**: Install QMK/Vial drivers if needed
- **Bootloader Mode**: Try entering bootloader mode

#### Trackball Not Working
- **Sensor Alignment**: Verify PMW3360 is properly seated
- **Lens Cleaning**: Clean trackball and sensor lens
- **Firmware Check**: Ensure trackball support is enabled

#### Encoder Issues
- **Mechanical Check**: Verify encoder is securely mounted
- **Electrical Test**: Check continuity of encoder pins
- **Debouncing**: Adjust debounce settings if needed

#### Split Communication Problems
- **Cable Check**: Test TRRS cable with multimeter
- **Jack Inspection**: Ensure TRRS jacks are properly soldered
- **Firmware Sync**: Verify both halves have correct firmware

### Debug Mode

Enable debug output in QMK:
```c
#define DEBUG_ENABLE
#define DEBUG_MATRIX
#define DEBUG_KEYBOARD
```

### Support Resources

- 📖 [QMK Documentation](https://docs.qmk.fm/)
- 💬 [QMK Discord](https://discord.gg/qmk)
- 🎮 [Vial Documentation](https://get.vial.today/docs/)
- 🐛 [Issue Tracker](../../issues)

---

## 🤝 Contributing

We welcome contributions to make RattusBoard even better! Here's how you can help:

### Ways to Contribute

- **🐛 Bug Reports**: Found an issue? Let us know!
- **💡 Feature Requests**: Have ideas for improvements?
- **📝 Documentation**: Help improve guides and tutorials
- **🔧 Code**: Submit pull requests for firmware improvements
- **📸 Media**: Share photos of your build!

### Development Setup

1. **Fork the Repository**: Create your own fork
2. **Clone Locally**: `git clone your-fork-url`
3. **Create Branch**: `git checkout -b feature/your-feature`
4. **Make Changes**: Implement your improvements
5. **Test Thoroughly**: Verify changes work as expected
6. **Submit PR**: Create pull request with detailed description

### Automated Firmware Builds

The repository includes GitHub Actions automation for firmware building:

#### 🔄 **Continuous Integration**
- **Pull Request Builds**: Every PR automatically builds firmware to catch issues early
- **Main Branch Builds**: Commits to main trigger development builds
- **Release Builds**: Tagged releases automatically build and attach firmware files

#### 📦 **Build Artifacts**
- **PR/Development Builds**: Available as workflow artifacts for 90 days
- **Release Builds**: Permanently attached to GitHub releases
- **Split Firmware**: Available as separate left/right artifacts (`rattusboard_left-rp2040_pro_micro-firmware` and `rattusboard_right-rp2040_pro_micro-firmware`)
- **Legacy Build**: Also available as `rattusboard_latest.uf2` from existing workflows

#### 🛠️ **Local Development**
```bash
# Validate keyboard configuration
python3 -m json.tool keyboards/rattusboard/info.json

# Check required files
ls keyboards/rattusboard/{config.h,rules.mk,info.json,rattusboard.{h,c}}

# Test with QMK (requires QMK setup)
qmk compile -kb rattusboard -km default
```

### Code Standards

- Follow QMK coding conventions
- Comment complex logic clearly
- Test changes on actual hardware
- Update documentation as needed

---

## 📜 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

### Third-Party Components

- **QMK Firmware**: GPL v2 License
- **Vial**: GPL v3 License
- **PMW3360 Library**: MIT License

---

## 🙏 Acknowledgments

Special thanks to:

- **QMK Team**: For the incredible firmware foundation
- **Vial Team**: For real-time keymap editing capabilities
- **Corne Community**: For the ergonomic layout inspiration
- **foostan**: Original Corne keyboard designer
- **RP2040 Community**: For Raspberry Pi Pico support

---

<div align="center">

**Made with ❤️ by the keyboard community**

*Happy typing! 🎹*

</div>
