# MCU configuration for Raspberry Pi Pico (RP2040)
MCU = RP2040
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# Split keyboard support
SPLIT_KEYBOARD = yes

# PMW3360 trackball support
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360

# Encoder support for scroll wheel
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# VIA support (VIAL is handled via keyboard.json now)
VIA_ENABLE = yes

# Optional features (can be enabled as needed)
LTO_ENABLE = yes            # Link Time Optimization for smaller firmware
SPACE_CADET_ENABLE = no     # Disable Space Cadet Shift to save space
GRAVE_ESC_ENABLE = no       # Disable Grave Escape to save space
MAGIC_ENABLE = no           # Disable Magic keycodes to save space

# RP2040 specific optimizations
OPT_DEFS += -DHAL_USE_SPI=TRUE
OPT_DEFS += -DSPI_USE_WAIT=TRUE
OPT_DEFS += -DSPI_SELECT_MODE=SPI_SELECT_MODE_PAD

# Custom source files
SRC += matrix.c