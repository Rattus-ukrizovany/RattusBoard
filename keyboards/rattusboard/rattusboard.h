// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "quantum.h"

/*
 * RattusBoard Layout Definition
 * 
 * This is a fully independent split layout with 3x7 matrix per half.
 * Each half has its own dedicated pins - no shared matrix.
 * 
 * Layout is defined in keyboard.json for proper QMK split handling.
 */

// Layout macro removed - now handled by QMK split system via keyboard.json

/*
 * Custom keycodes for RattusBoard specific features
 */
enum rattusboard_keycodes {
    TB_TOG = QK_KB_0,  // Toggle trackball mode (cursor/scroll)
    TB_DPI_UP,         // Increase trackball DPI
    TB_DPI_DN,         // Decrease trackball DPI
    TB_RESET           // Reset trackball settings
};