// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

/* 
 * Matrix configuration is now defined in keyboard.json
 * This file contains RP2040-specific and advanced configuration only
 */

/* 
 * PMW3360 Trackball Configuration
 * Using SPI interface on RP2040
 */
#define PMW33XX_CS_PIN GP22
#define PMW33XX_CPI 1600

/* SPI Configuration for PMW3360 */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP23
#define SPI_MOSI_PIN GP24
#define SPI_MISO_PIN GP25

/*
 * Advanced split keyboard settings
 */
#define SPLIT_USB_DETECT
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_OLED_ENABLE

/*
 * RP2040 specific settings
 */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP28

/* 
 * Advanced features
 */
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

/* Mouse key settings for smooth trackball operation */
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_TIME_TO_MAX 20
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 80
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40