// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

/* key matrix size - each half is independent */
#define MATRIX_ROWS 7
#define MATRIX_COLS 3

/* 
 * Keyboard Matrix Assignments (Raspberry Pi Pico / RP2040)
 * 
 * FULLY INDEPENDENT HALVES - NO SHARED PINS
 * Each half has its own dedicated 3x7 matrix
 * 
 * Left Half (Master):
 * - Rows: GP2, GP3, GP4, GP5, GP6, GP7, GP8 
 * - Cols: GP9, GP10, GP11
 * 
 * Right Half (Slave):
 * - Rows: GP2, GP3, GP4, GP5, GP6, GP7, GP8
 * - Cols: GP12, GP13, GP14
 */
#define MATRIX_ROW_PINS { GP2, GP3, GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP9, GP10, GP11 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* 
 * Split keyboard settings 
 */
#define SPLIT_HAND_PIN GP16
#define SPLIT_HAND_PIN_LOW_IS_LEFT
#define SOFT_SERIAL_PIN GP1
#define SPLIT_USB_DETECT

/* 
 * PMW3360 Trackball Configuration
 * Using SPI interface on RP2040
 */
#define POINTING_DEVICE_ENABLE
#define POINTING_DEVICE_DRIVER pmw3360
#define PMW3360_CS_PIN GP17
#define PMW3360_CPI 1600

/* SPI Configuration for PMW3360 */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20

/*
 * Rotary Encoder Configuration (Mouse Wheel)
 * Connected to right half for scroll wheel functionality
 */
#define ENCODERS_PAD_A { GP21 }
#define ENCODERS_PAD_B { GP22 }
#define ENCODER_RESOLUTION 4

/* Enable encoder mapping */
#define ENCODER_MAP_ENABLE

/*
 * Feature flags
 */
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_OLED_ENABLE

/*
 * RP2040 specific settings
 */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25

/* 
 * Advanced features
 */
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

/* Mouse key settings for smooth trackball operation */
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_MAX_SPEED 6
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 80
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40