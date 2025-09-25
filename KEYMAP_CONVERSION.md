# RattusBoard Keymap Conversion from ZMK

This document describes the keymap conversion from the original ZMK configuration to QMK format.

## Original ZMK Source
The keymap was converted from: [corne-zmk-config](https://github.com/Rattus-ukrizovany/corne-zmk-config)

## Layer Structure Changes

| ZMK Layer | QMK Layer | Description |
|-----------|-----------|-------------|
| `DEFAULT_L` (0) | `_DEFAULT` (0) | Base QWERTY layer |
| `SYMBOLS_L` (1) | `_SYMBOLS` (1) | Numbers and symbols (left thumb) |
| `ARROWS_L` (2) | `_ARROWS` (2) | F-keys, media, navigation (right thumb) |
| `NUMBERS_L` (3) | `_NUMBERS` (3) | Additional layer via layer-tap on Enter |
| Flash (conditional) | `_ADJUST` (4) | System controls, trackball, mouse |

## Key Differences

### Base Layer (_DEFAULT)
- **ZMK**: TAB, LEFT_SHIFT, LEFT_CONTROL modifiers
- **QMK**: Matches exactly - `KC_TAB`, `KC_LSFT`, `KC_LCTL`

### Layer Activation
- **ZMK**: `&mo 1` (Symbols), `&mo 2` (Arrows), `&lt 3 ENTER` (Numbers)
- **QMK**: `SYMBOLS`, `ARROWS`, `LT(_NUMBERS, KC_ENT)`

### System Controls
- **ZMK**: `&bt BT_CLR_ALL`, `&sys_reset`, `&bootloader`
- **QMK**: `QK_BOOT` (unified reset functionality)

### Encoder Configuration
Enhanced encoder support with layer-specific functions:
- **_DEFAULT**: Scroll wheel (up/down)
- **_SYMBOLS**: Volume control
- **_ARROWS**: Horizontal scroll
- **_NUMBERS**: Page up/down
- **_ADJUST**: Brightness control

## Features Retained

- ✅ Split keyboard functionality
- ✅ PMW3360 trackball integration
- ✅ Rotary encoder support
- ✅ Vial compatibility
- ✅ All original key assignments
- ✅ Layer logic and activation patterns

## Build Instructions

```bash
# Compile firmware
qmk compile -kb rattusboard -km default

# The build produces a single .uf2 file that works on both halves
# Thanks to hardware hand detection via GP21 pin
```

## Notes

- No changes needed to hardware wiring
- Single firmware file works for both halves (hardware auto-detection)
- Vial configuration remains compatible
- All trackball and encoder features preserved