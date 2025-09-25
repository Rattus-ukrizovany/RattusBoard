# 🐭 RattusBoard

*A premium QMK-powered split ergonomic keyboard with integrated trackball and encoder*

[![QMK Firmware](https://img.shields.io/badge/QMK-Firmware-blue.svg)](https://qmk.fm/)
[![Vial Support](https://img.shields.io/badge/Vial-Supported-green.svg)](https://get.vial.today/)
[![License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](LICENSE)

---

## ⚡ Quick Summary

- 👉 **[Build Guide and Pinout](HALVES_WIRING.md)** — Wiring diagrams, pin assignments, and hardware tips
- 📝 **[Keymap & Layers](keymaps/default/keymap.c)** — See the default layout and layer logic
- 🖥️ **[Firmware Downloads](https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest)** — Get the latest `.uf2` for both halves
- 🚀 **[Firmware Flashing Instructions](#-firmware-flashing--split-setup-important-clarification)** — One firmware file for both halves!
- 🧑‍💻 **[QMK Documentation](https://docs.qmk.fm/)** & **[Vial Info](https://get.vial.today/)** — Customization and live remapping
- 🐞 **[Troubleshooting Guide](#-troubleshooting-reference)** — Common problems & solutions
- 💬 **[Open an Issue](https://github.com/Rattus-ukrizovany/RattusBoard/issues/new/choose)** — Need help? Found a bug? Suggest a feature!

---
## 🌟 Overview

RattusBoard is a cutting-edge split ergonomic keyboard designed for productivity enthusiasts and professionals who demand precision, comfort, and customization. Built on the robust QMK firmware for the RP2040 platform, RattusBoard features a trackball, rotary encoder, and real-time keymap editing via Vial.

### ✨ Key Features

- **Ergonomic Split Design**: Based on the Corne layout for optimal hand positioning
- **Integrated Trackball**: PMW3360 sensor for precise cursor control
- **Rotary Encoder**: Smooth, customizable input
- **QMK Firmware**: Layers, macros, and advanced features
- **Vial Support**: Real-time keymap editing (no reflashing required)
- **Raspberry Pi Pico**: RP2040 microcontroller
- **Customizable & Open-source**: Designed for modding and improvements

---

## 📋 Hardware Specifications

See the previous README for detailed specs, or consult the wiring guides for pinouts and matrix info.

---

## 🛠️ Build Guide

Follow the wiring diagrams and pin assignments in the repo. Each half has independent matrix wiring and uses the GP16 pin for hand detection (see below).

---

## 🚀 Firmware Flashing & Split Setup (IMPORTANT CLARIFICATION)

### Quick Summary:
**You only need to flash ONE firmware file (`rattusboard_default.uf2`) to both halves of your keyboard.**

#### How RattusBoard's Split Detection Works
- **Hardware hand detection**: Using the GP16 pin, the keyboard auto-detects which half is left or right. (GP16 connected to GND = left/master, GP16 floating = right/slave.)
- **Same firmware file**: No need to build or download separate left/right .uf2 files. The firmware is designed to work out-of-the-box for both halves.
- **Peripherals**: Trackball and encoder are on the right half; the firmware automatically enables their functions only on the correct side.

#### Step-by-Step Flashing Instructions

1. **Download the latest firmware release**  
   Go to [Releases](https://github.com/Rattus-ukrizovany/RattusBoard/releases). Download `rattusboard_default.uf2`.

2. **Flash BOTH halves with the SAME file**  
   - Hold BOOTSEL and plug in USB on each Pico to enter bootloader mode.
   - Drag `rattusboard_default.uf2` onto the shown RPI-RP2 drive.
   - Repeat for both Picos.

3. **Connect and Test**  
   - Connect halves with TRRS cable.
   - Plug USB into the left half (master).
   - Both halves should work automatically.

#### Advanced Note
- **For developers/testing**: You can build separate left/right firmware if you want to experiment with custom features, but this is *not required* for normal assembly or use.

#### Troubleshooting
- If one half doesn't work:
  - Check TRRS cable and jacks
  - Ensure both halves flashed with SAME firmware file
  - Verify GP16 hand detection wiring on each half
  - Use online key tester or QMK debug output for diagnosis
- No need to rebuild or reflash separate files unless pursuing advanced development.

---

## 🎹 Keymap & Layers

- Four-layer layout adapted from Corne, with integrated trackball and encoder.
- Vial support for live keymap editing.
- See [HALVES_WIRING.md](HALVES_WIRING.md) and [keymaps/default/keymap.c](keymaps/default/keymap.c) for details.

---

## 💻 Vial & QMK Support

- Vial: Works out-of-the-box with the included firmware. Download Vial app from [get.vial.today](https://get.vial.today).
- QMK: Use `qmk compile -kb rattusboard -km default` for custom builds. See QMK docs for advanced usage.

---

## ⚡ Firmware Downloads

- Always use the latest release file for flashing both halves:  
  [Download Latest Firmware (.uf2)](https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest/download/rattusboard_default.uf2)

- **Do NOT** download separate left/right files for typical use. Ignore any older instructions or workflow artifacts suggesting two files are needed.

---

## 🧪 Troubleshooting Reference

| Problem               | Solution                                                             |
|-----------------------|----------------------------------------------------------------------|
| Pico not detected     | Try a different USB cable, ensure BOOTSEL is pressed during connect  |
| Only one half works   | Check TRRS wiring, ensure both halves flashed with same firmware     |
| Keys not registering  | Check matrix wiring, use key tester website                         |
| Trackball/encoder     | Check wiring, clean sensor, ensure on right half                     |

---

## 🧪 Virtual Firmware Test Environment

### GitHub Codespaces Quick Start

The RattusBoard repository includes a complete virtual testing environment that automatically downloads the latest firmware and runs it in Renode simulation. This is perfect for testing firmware without physical hardware.

#### Automatic Setup

1. **Open in Codespaces**: Click the green "Code" button → "Codespaces" → "Create codespace on main"
2. **Wait for setup**: The environment automatically:
   - Installs QMK, Renode, and all dependencies 
   - Downloads the latest firmware release (`rattusboard_default.uf2`)
   - Sets up the complete development environment (~3-4 minutes)
3. **Start testing**: Run `rattusboard-test-firmware` to test firmware in Renode

#### Available Commands

| Command | Description |
|---------|-------------|
| `rattusboard-test-firmware` | Download latest firmware and run in Renode (one-step testing) |
| `rattusboard-test-firmware -i` | Start interactive Renode session with firmware loaded |
| `rattusboard-test-firmware -t` | Run automated tests only (no interactive mode) |
| `rattusboard-test-firmware -l` | Test left half configuration |
| `rattusboard-test-firmware -r` | Test right half configuration |
| `rattusboard-download-firmware` | Download latest firmware without testing |
| `rattusboard-download-firmware -l` | List all available firmware files |
| `rattusboard-download-firmware -a` | Download all firmware variants |
| `rattusboard-dev` | Show help and available tools |

#### Manual Firmware Testing

If you want to test a specific firmware file or use alternate firmware:

```bash
# Download a specific firmware file
rattusboard-download-firmware rattusboard_left.uf2

# Test specific firmware 
rattusboard-test-firmware -s rattusboard_left.uf2

# Download from a specific release tag
rattusboard-download-firmware --tag v1.2.0 rattusboard_default.uf2

# Force re-download latest firmware
rattusboard-download-firmware -f
```

#### Interactive Renode Testing

In interactive mode, you can test various keyboard functions:

```bash
# Start interactive session
rattusboard-test-firmware -i

# Available test commands in Renode:
test_matrix_left      # Test left half key matrix
test_matrix_right     # Test right half key matrix  
test_trackball        # Test PMW3360 trackball sensor
test_encoder          # Test rotary encoder
configure_left        # Switch to left half mode
configure_right       # Switch to right half mode
demo_keyboard_sequence # Run full demo sequence
```

#### Troubleshooting

**Firmware Download Issues:**
- Check internet connection in Codespace
- Try `rattusboard-download-firmware -f` to force re-download
- Use `rattusboard-download-firmware -l` to see available files
- Manually download from [Releases](https://github.com/Rattus-ukrizovany/RattusBoard/releases/latest) if needed

**Renode Simulation Issues:**
- Ensure firmware compiled successfully: `qmk compile -kb rattusboard -km default`
- Check ELF file exists: `ls -la .build/rattusboard_default.elf`
- Try test-only mode: `rattusboard-test-firmware -t`
- Restart with fresh firmware: `rattusboard-test-firmware -f`

**Common Error Solutions:**
- "ELF file not found" → Run `qmk compile -kb rattusboard -km default` first
- "Download failed" → Check network, try `-f` flag to force download
- "Renode not found" → Environment setup incomplete, restart Codespace
- "Permission denied" → Scripts should be executable in devcontainer

**Manual Troubleshooting Steps:**
```bash
# Check environment status
rattusboard-dev

# Verify tools are installed
renode --version
qmk --version

# Test environment
.devcontainer/test-environment.sh

# Manual firmware compile
qmk compile -kb rattusboard -km default

# Manual Renode start
renode sim/rattusboard.resc
```

#### Development Workflow

The virtual environment is perfect for:
- **Firmware Testing**: Test changes without flashing hardware
- **Feature Development**: Iterate quickly on new features  
- **Bug Reproduction**: Simulate specific scenarios
- **Learning**: Understand keyboard firmware behavior
- **Collaboration**: Share reproducible test environments

For hardware development and final validation, you'll still need to flash the actual RattusBoard, but this virtual environment handles most development and testing needs.

---

## 🤝 Contributing

- Bug reports, feature requests, documentation, code, and build photos are welcome!
- See CONTRIBUTING.md for details.

---

## 📜 License

This project is licensed under GPLv3. See [LICENSE](LICENSE).

---

## 🙏 Acknowledgments

Thanks to the QMK, Vial, Corne, and RP2040 communities!

---

**Made with ❤️ by the keyboard community. Happy typing!**
