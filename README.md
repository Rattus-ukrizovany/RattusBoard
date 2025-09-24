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

This section provides detailed pin assignments for the Raspberry Pi Pico (RP2040) microcontroller. **All pin assignments must match exactly between both halves for proper operation.**

#### Matrix Wiring (6x7 Corne-style Layout)

**Row Connections (Shared between both halves):**
```
Row 0: GP2  → Connect to all switches in row 0
Row 1: GP3  → Connect to all switches in row 1  
Row 2: GP4  → Connect to all switches in row 2
Row 3: GP5  → Connect to all switches in row 3
Row 4: GP6  → Connect to all switches in row 4
Row 5: GP7  → Connect to all switches in row 5
Row 6: GP8  → Connect to all switches in row 6 (thumb cluster)
```

**Column Connections:**

*Left Half (Slave):*
```
Col 0: GP9  → Connect to all switches in column 0 (left half)
Col 1: GP10 → Connect to all switches in column 1 (left half)
Col 2: GP11 → Connect to all switches in column 2 (left half)
```

*Right Half (Master):*
```
Col 3: GP12 → Connect to all switches in column 0 (right half)
Col 4: GP13 → Connect to all switches in column 1 (right half)
Col 5: GP14 → Connect to all switches in column 2 (right half)
```

**Diode Orientation:** COL2ROW (Cathode toward row, Anode toward column)

#### Split Communication

**TRRS Connection (both halves):**
```
GP1  → TRRS Tip (Serial communication)
GND  → TRRS Ring 1 (Ground)
VCC  → TRRS Ring 2 (Power)
NC   → TRRS Sleeve (Not connected)
```

**Split Detection:**
```
GP16 → Split hand detection pin
      → Connect to GND on RIGHT half only
      → Leave floating on LEFT half
```

#### PMW3360 Trackball Sensor (Right Half Only)

**SPI Connection:**
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
Motion pin: Can be connected to GP23 for motion detection (optional)
Reset pin: Connect to 3.3V through 10kΩ resistor
```

#### Rotary Encoder (Right Half Only)

**Encoder Connections:**
```
GP21 → Encoder Pin A
GP22 → Encoder Pin B  
GND  → Encoder Common/Ground
```

**Encoder Switch (if present):**
```
GP24 → Encoder switch pin (optional)
GND  → Encoder switch ground
```

#### Power and USB

**USB Connection (Right Half Only):**
```
USB-C connector wired to Pico's native USB pins
GP25 → Status LED (optional)
```

**Power Distribution:**
- 3.3V and GND must be shared between halves via TRRS cable
- Both Picos powered from right half (master)

#### Important Wiring Notes

⚠️ **Critical Requirements:**
- All GND connections must be solid and continuous
- Use twisted pair or shielded cable for TRRS connection
- Keep high-speed signals (SPI) away from matrix wiring
- Test continuity of all connections before powering up

🔧 **Wiring Tips:**
- Use different colored wires for rows vs columns
- Label all connections during assembly
- Take photos before closing the case
- Use flux for all solder joints
- Test each half independently before connecting

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

#### Method 1: Pre-compiled Firmware (Recommended)
1. Download the latest firmware from [Releases](../../releases)
2. Put Pico in bootloader mode (hold BOOTSEL while connecting USB)
3. Drag and drop `.uf2` file to mounted drive
4. Repeat for second half

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
