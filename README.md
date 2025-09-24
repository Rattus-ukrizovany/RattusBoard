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

> **📖 [Complete Detailed Wiring Instructions → HALVES_WIRING.md](HALVES_WIRING.md)**

This section provides essential wiring information for the RattusBoard split keyboard. For comprehensive assembly instructions, troubleshooting, and detailed diagrams, see the **[detailed wiring guide](HALVES_WIRING.md)**.

#### 🔍 Quick Overview

```
Left Half (Master)              Right Half (Slave)
┌─────────────────┐            ┌─────────────────┐
│  [USB-C INPUT]  │            │                 │
│ Raspberry Pi    │◄── TRRS ──►│ Raspberry Pi    │
│ Pico            │            │ Pico            │
│                 │            │                 │
│ Matrix: 3×7     │            │ Matrix: 3×7     │
│ GP16 → GND      │            │ GP16 (floating) │
└─────────────────┘            │ [PMW3360]       │
                               │ [Encoder]       │
                               └─────────────────┘
```

#### 📋 Essential Pin Assignments

| Component | Left Half | Right Half | Notes |
|-----------|-----------|------------|-------|
| **Matrix Rows** | GP2-GP8 | GP2-GP8 | Shared across both halves |
| **Matrix Cols** | GP9-GP11 | GP12-GP14 | 3 columns per half |
| **Split Comm** | GP1 | GP1 | TRRS serial connection |
| **Hand Detection** | GP16→GND | GP16 (float) | **Critical configuration** |
| **USB Power** | Native | - | Left half only |
| **Trackball SPI** | - | GP17-GP20 | Right half only |
| **Encoder** | - | GP21-GP22 | Right half only |

#### ⚠️ Critical Requirements

- **Diode Orientation**: COL2ROW (cathode band toward row pins)
- **Hand Detection**: LEFT half GP16→GND, RIGHT half GP16 floating
- **TRRS Cable**: 4-conductor cable required (not 3-conductor TRS)
- **Power Flow**: USB → Left half → TRRS → Right half
- **Testing**: Verify each half independently before connecting together

#### 🔧 Quick Assembly Steps

1. **Install diodes** with correct polarity (band toward row)
2. **Wire matrix** according to pin assignments above  
3. **Configure hand detection** (GP16→GND on left only)
4. **Install TRRS jacks** and verify cable connectivity
5. **Add peripherals** (trackball, encoder on right half)
6. **Test thoroughly** before final assembly

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
5. **USB-C**: Install on master half only

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

### Flashing Process

#### Method 1: Pre-compiled Firmware (Recommended) ⭐
1. **Download** the latest firmware:
   - **[Direct Download](https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest/download/rattusboard_latest.uf2)** (Latest version)
   - Or browse **[All Releases](https://github.com/Rattus-ukrizovany/RattusBoard/releases)** for specific versions
2. **Prepare the first Raspberry Pi Pico**:
   - Hold **BOOTSEL** button while connecting USB cable
   - Pico will appear as a USB drive named "RPI-RP2"
3. **Flash the firmware**:
   - Drag and drop the `.uf2` file to the "RPI-RP2" drive
   - The Pico will automatically reboot with new firmware
4. **Repeat for the second half** (right side of keyboard)

#### Method 2: Compile from Source
```bash
# Navigate to QMK directory
cd qmk_firmware

# Copy keyboard files (if not done already)
cp -r /path/to/RattusBoard/keyboards/rattusboard keyboards/

# Compile firmware
qmk compile -kb rattusboard -km default

# Flash to keyboard
qmk flash -kb rattusboard -km default
```

#### Method 3: Using QMK Configurator
1. Upload the `info.json` file to [QMK Configurator](https://config.qmk.fm/)
2. Design your keymap visually
3. Download the compiled firmware
4. Flash using QMK Toolbox

#### Bootloader Mode
- **Initial Flash**: Hold BOOTSEL button while connecting USB
- **Subsequent Flashes**: Use reset button or `QK_BOOT` key in keymap

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
                           Trackball    Encoder
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
- **Latest Build**: Always available as `rattusboard_latest.uf2`

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
