# QMK/VIAL Setup for RattusBoard

## Overview

RattusBoard now fully supports both QMK and VIAL firmware compilation! The keyboard configuration has been updated to modern QMK standards.

## Quick Start

### Prerequisites
- QMK CLI installed: `pip install qmk`
- QMK setup: `qmk setup --yes`

### Building Firmware

1. **Copy keyboard files to QMK**:
   ```bash
   cp -r keyboards/rattusboard ~/.local/share/qmk/keyboards/
   ```

2. **Build default QMK firmware**:
   ```bash
   qmk compile -kb rattusboard -km default
   ```

3. **Build VIAL firmware**:
   ```bash
   qmk compile -kb rattusboard -km vial
   ```

## Firmware Variants

### 1. Default QMK (`rattusboard_default.uf2`)
- Standard QMK firmware with VIA support
- Full feature set including trackball and encoder
- Compatible with VIA app for keymap editing

### 2. VIAL (`rattusboard_vial.uf2`)
- VIAL-enabled firmware for advanced customization
- Live keymap editing without reflashing
- Compatible with VIAL app
- Includes all QMK features

## Key Changes Made

### 1. **Modern QMK Structure**
- ✅ Moved from `info.json` to `keyboard.json`
- ✅ Removed layout macro from `.h` file, defined in JSON
- ✅ Split configuration properly organized

### 2. **Fixed Configuration Conflicts**
- ✅ Resolved encoder pin definition conflicts
- ✅ Cleaned up duplicate feature definitions
- ✅ Updated mouse keycode naming (KC_MS_* → MS_*)

### 3. **Added VIAL Support**
- ✅ Created dedicated VIAL keymap
- ✅ Enabled VIAL features with proper configuration
- ✅ Maintained compatibility with existing VIAL JSON

### 4. **Updated Build System**
- ✅ Fixed compilation workflow
- ✅ Both QMK and VIAL variants build successfully
- ✅ No warnings or errors in compilation

## Installation

1. Download the appropriate `.uf2` file:
   - `rattusboard_default.uf2` for standard QMK
   - `rattusboard_vial.uf2` for VIAL support

2. Hold BOOTSEL button and plug in USB to enter bootloader mode
3. Drag the `.uf2` file to the RPI-RP2 drive
4. Repeat for both halves (same firmware file works for both)

## Features Verified

- ✅ **Split keyboard functionality** with auto hand detection
- ✅ **PMW3360 trackball integration** on right half
- ✅ **Rotary encoder support** on right half  
- ✅ **VIA/VIAL compatibility** for keymap editing
- ✅ **All QMK features** (NKRO, mouse keys, layers, etc.)
- ✅ **RP2040 optimizations** and configurations

## Automated Building

The GitHub Actions workflow now automatically builds both firmware variants on every push/PR. Releases include both versions.

## Troubleshooting

If you encounter issues:

1. **Clean build**: Remove `.build` directory and rebuild
2. **Check QMK version**: Ensure you're using QMK CLI 1.1.8+
3. **Update submodules**: `qmk setup --yes` to update QMK codebase
4. **Verify files**: Ensure all keyboard files are properly copied to QMK directory

## Development

For development:

1. Make changes to files in `keyboards/rattusboard/`
2. Copy to QMK: `cp -r keyboards/rattusboard ~/.local/share/qmk/keyboards/`
3. Test build: `qmk compile -kb rattusboard -km default`
4. Commit changes to repository

Both keymaps share the same base configuration but the VIAL keymap enables additional runtime customization features.