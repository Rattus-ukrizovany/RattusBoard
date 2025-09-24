# 🐭 RattusBoard

*A premium QMK-powered split ergonomic keyboard with integrated trackball and encoder*

[![QMK Firmware](https://img.shields.io/badge/QMK-Firmware-blue.svg)](https://qmk.fm/)
[![Vial Support](https://img.shields.io/badge/Vial-Supported-green.svg)](https://get.vial.today/)
[![License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](LICENSE)

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
