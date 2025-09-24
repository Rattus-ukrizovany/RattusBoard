// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "quantum.h"

/*
 * RattusBoard Layout Definition
 * 
 * This is a 6x7 matrix in a Corne-style split layout.
 * 
 *   Left Half (L00-L35)          Right Half (R00-R35)
 * ┌─────┬─────┬─────┐          ┌─────┬─────┬─────┐
 * │ L00 │ L01 │ L02 │          │ R00 │ R01 │ R02 │  Row 0
 * ├─────┼─────┼─────┤          ├─────┼─────┼─────┤
 * │ L10 │ L11 │ L12 │          │ R10 │ R11 │ R12 │  Row 1
 * ├─────┼─────┼─────┤          ├─────┼─────┼─────┤
 * │ L20 │ L21 │ L22 │          │ R20 │ R21 │ R22 │  Row 2
 * ├─────┼─────┼─────┤          ├─────┼─────┼─────┤
 * │ L30 │ L31 │ L32 │          │ R30 │ R31 │ R32 │  Row 3
 * ├─────┼─────┼─────┤          ├─────┼─────┼─────┤
 * │ L40 │ L41 │ L42 │          │ R40 │ R41 │ R42 │  Row 4
 * ├─────┼─────┼─────┤          ├─────┼─────┼─────┤
 * │ L50 │ L51 │ L52 │          │ R50 │ R51 │ R52 │  Row 5
 * └─────┴─────┼─────┤          ├─────┼─────┴─────┘
 *             │ L60 │ L61 │ L62 │ R60 │ R61 │ R62 │    Row 6 (thumbs)
 *             └─────┴─────┴─────┴─────┴─────┴─────┘
 *                                   Trackball  Encoder
 */

#define LAYOUT_split_3x6_3( \
    L00, L01, L02,                         R00, R01, R02, \
    L10, L11, L12,                         R10, R11, R12, \
    L20, L21, L22,                         R20, R21, R22, \
    L30, L31, L32,                         R30, R31, R32, \
    L40, L41, L42,                         R40, R41, R42, \
    L50, L51, L52,                         R50, R51, R52, \
              L60, L61, L62,         R60, R61, R62  \
) \
{ \
    { L00, L01, L02, R00, R01, R02 }, \
    { L10, L11, L12, R10, R11, R12 }, \
    { L20, L21, L22, R20, R21, R22 }, \
    { L30, L31, L32, R30, R31, R32 }, \
    { L40, L41, L42, R40, R41, R42 }, \
    { L50, L51, L52, R50, R51, R52 }, \
    { L60, L61, L62, R60, R61, R62 }  \
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