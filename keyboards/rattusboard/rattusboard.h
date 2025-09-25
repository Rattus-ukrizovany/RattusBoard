// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "quantum.h"

/*
 * RattusBoard Layout Definition
 * 
 * 3x6 Corne-style split layout with 3 thumb keys per side
 * Matrix: 4 rows x 6 cols per half (4th row = thumb keys)
 */

#define LAYOUT_split_3x6_3( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
                   L33, L34, L35,           R30, R31, R32 \
) \
{ \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { KC_NO, KC_NO, KC_NO, L33, L34, L35 }, \
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { R30, R31, R32, KC_NO, KC_NO, KC_NO } \
}

/*
 * Custom keycodes for RattusBoard specific features
 */
enum rattusboard_keycodes {
    TB_TOG = QK_KB_0,  // Toggle trackball mode (cursor/scroll)
    TB_DPI_UP,         // Increase trackball DPI
    TB_DPI_DN,         // Decrease trackball DPI
    TB_RESET           // Reset trackball settings
};