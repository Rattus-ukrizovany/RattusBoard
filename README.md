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

#### Development Environment (Optional)
```bash
# Install QMK CLI
pip3 install qmk

# Set up QMK environment
qmk setup

# Clone RattusBoard configuration
git clone https://github.com/Rattus-ukrizovany/RattusBoard-QMK
```

### Flashing Process

#### Method 1: Pre-compiled Firmware (Recommended)
1. Download the latest firmware from [Releases](../../releases)
2. Put Pico in bootloader mode (hold BOOTSEL while connecting)
3. Drag and drop `.uf2` file to mounted drive
4. Repeat for second half

#### Method 2: Compile from Source
```bash
# Navigate to QMK directory
cd qmk_firmware

# Compile firmware
qmk compile -kb rattusboard -km default

# Flash to keyboard
qmk flash -kb rattusboard -km default
```

#### Bootloader Mode
- **Initial Flash**: Hold BOOTSEL button while connecting USB
- **Subsequent Flashes**: Use reset button or keymap reset key

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

## 📞 Contact & Support

- **Issues**: [GitHub Issues](../../issues)
- **Discussions**: [GitHub Discussions](../../discussions)
- **Email**: [Contact Information]
- **Social**: [Social Media Links]

---

<div align="center">

**Made with ❤️ by the keyboard community**

*Happy typing! 🎹*

</div>