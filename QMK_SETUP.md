# QMK/VIAL Setup for RattusBoard

## Overview

RattusBoard now fully supports VIAL firmware compilation using the official VIAL-QMK repository! The keyboard configuration has been updated to work with the VIAL-QMK fork for proper VIAL functionality.

## Quick Start

### Prerequisites
- QMK CLI installed: `pip install qmk`

### Building Firmware with VIAL-QMK

1. **Clone VIAL-QMK repository**:
   ```bash
   git clone https://github.com/vial-kb/vial-qmk.git
   cd vial-qmk
   git submodule update --init --recursive
   ```

2. **Set up QMK to use VIAL-QMK**:
   ```bash
   qmk config user.qmk_home=$(pwd)
   ```

3. **Copy RattusBoard keyboard files to VIAL-QMK**:
   ```bash
   cp -r /path/to/rattusboard/keyboards/rattusboard keyboards/
   ```

4. **Build VIAL firmware**:
   ```bash
   qmk compile -kb rattusboard -km vial
   ```

## Firmware Variants

### VIAL (`rattusboard_vial.uf2`)
- **Primary firmware** - VIAL-enabled firmware for advanced customization
- Live keymap editing without reflashing using VIAL app
- Compatible with VIAL app from [get.vial.today](https://get.vial.today)
- Includes all QMK features plus VIAL-specific enhancements
- Built using the official VIAL-QMK repository

## Key Changes Made

### 1. **VIAL-QMK Integration**
- ✅ Switched to using official VIAL-QMK repository
- ✅ Added proper VIAL keyboard UID configuration
- ✅ Created VIAL-specific configuration files

### 2. **Updated Build System**
- ✅ Modified CI workflow to clone and use VIAL-QMK
- ✅ VIAL firmware builds successfully with all features
- ✅ No warnings or errors in compilation

### 3. **Enhanced VIAL Support**
- ✅ Proper `config.h` with VIAL_KEYBOARD_UID
- ✅ Updated `vial.json` for keyboard layout definition
- ✅ Maintained compatibility with existing trackball and encoder features

## Installation

1. Download the `.uf2` file:
   - `rattusboard_vial.uf2` for VIAL support (recommended)

2. Hold BOOTSEL button and plug in USB to enter bootloader mode
3. Drag the `.uf2` file to the RPI-RP2 drive
4. Repeat for both halves (same firmware file works for both)

## Features Verified

- ✅ **Split keyboard functionality** with auto hand detection
- ✅ **PMW3360 trackball integration** on right half
- ✅ **Rotary encoder support** on right half  
- ✅ **VIAL compatibility** for live keymap editing
- ✅ **All QMK features** (NKRO, mouse keys, layers, etc.)
- ✅ **RP2040 optimizations** and configurations

## Automated Building

The GitHub Actions workflow now automatically builds VIAL firmware using the official VIAL-QMK repository on every push/PR. Releases include the compiled firmware.

## Troubleshooting

If you encounter issues:

1. **Clean build**: Remove `.build` directory and rebuild
2. **Check QMK version**: Ensure you're using QMK CLI 1.1.8+
3. **Update submodules**: `qmk setup --yes` to update QMK codebase
4. **Verify files**: Ensure all keyboard files are properly copied to QMK directory

## Development

For development:

1. Clone VIAL-QMK: `git clone https://github.com/vial-kb/vial-qmk.git`
2. Set up submodules: `cd vial-qmk && git submodule update --init --recursive`
3. Configure QMK home: `qmk config user.qmk_home=$(pwd)`
4. Copy keyboard files: `cp -r /path/to/rattusboard/keyboards/rattusboard keyboards/`
5. Make changes to files in `keyboards/rattusboard/`
6. Test build: `qmk compile -kb rattusboard -km vial`
7. Commit changes to RattusBoard repository

The VIAL firmware provides live keymap editing capabilities without requiring reflashing.