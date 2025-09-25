// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "quantum.h"

/*
 * RattusBoard Layout Definition
 * 
 * Layout macro is now defined in keyboard.json
 * 3x6 Corne-style split layout with 3 thumb keys per side
 * Matrix: 4 rows x 6 cols per half (4th row = thumb keys)
 */

/*
 * Custom keycodes for RattusBoard specific features
 */
enum rattusboard_keycodes {
    TB_TOG = QK_KB_0,  // Toggle trackball mode (cursor/scroll)
    TB_DPI_UP,         // Increase trackball DPI
    TB_DPI_DN,         // Decrease trackball DPI
    TB_RESET           // Reset trackball settings
};