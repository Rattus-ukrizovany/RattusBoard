// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include "matrix.h"
#include "quantum.h"
#include "debug.h"
#include "split_common/split_util.h"

/*
 * Custom matrix implementation for RattusBoard
 * 
 * New Layout: 3x6 main grid + thumb row (row 3)
 * Matrix per half: 4 rows x 6 columns
 * 
 * Thumb cluster arrangement:
 * - Left half: columns 3, 4, 5 (row 3)
 * - Right half: columns 0, 1, 2 (row 3)
 * 
 * Physical Design:
 * - Left half: Rows GP2-GP5, Cols GP9-GP14
 * - Right half: Rows GP2-GP5, Cols GP15-GP20
 * 
 * QMK Implementation: Standard 6x4 split matrix
 * - Left half scans columns 0-5 (physically GP9-GP14)
 * - Right half scans columns 0-5 (physically GP15-GP20)
 * - Diode direction: COL2ROW
 */

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// Matrix state
static matrix_row_t raw_matrix[MATRIX_ROWS];
static matrix_row_t matrix[MATRIX_ROWS];

#if (DEBOUNCE > 0)
static bool debouncing = false;
static uint16_t debouncing_time;
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
#endif

// Pin configurations
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_custom(void) {
    // Initialize row pins as input with pull-up
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        setPinInputHigh(row_pins[i]);
    }
    
    // Initialize column pins as output
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(col_pins[i]);
        writePinHigh(col_pins[i]);
    }
    
    // Initialize matrix state
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
#if (DEBOUNCE > 0)
        matrix_debouncing[i] = 0;
#endif
    }
    
    matrix_init_kb();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    
    // New layout: Each half scans all 6 columns (0-5)
    // Left half: GP9-GP14 (physical) -> columns 0-5 (logical)
    // Right half: GP15-GP20 (physical) -> columns 0-5 (logical)
    uint8_t col_start = 0;
    uint8_t col_end = MATRIX_COLS;
    
    // Scan the matrix (each half scans only its own physical pins)
    for (uint8_t col = col_start; col < col_end; col++) {
        // Select column (this will only activate pins present on this half)
        writePinLow(col_pins[col]);
        
        // Small delay for signal to propagate
        matrix_io_delay();
        
        // Read all rows for this column (each half reads its own pins)
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool key_pressed = !readPin(row_pins[row]);
            
            // Update matrix state
            if (key_pressed) {
                raw_matrix[row] |= (1 << col);
            } else {
                raw_matrix[row] &= ~(1 << col);
            }
        }
        
        // Deselect column
        writePinHigh(col_pins[col]);
    }
    
#if (DEBOUNCE > 0)
    // Debouncing logic
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (raw_matrix[i] != matrix_debouncing[i]) {
            debouncing = true;
            debouncing_time = timer_read();
            matrix_debouncing[i] = raw_matrix[i];
        }
    }
    
    if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            if (matrix[i] != matrix_debouncing[i]) {
                matrix[i] = matrix_debouncing[i];
                changed = true;
            }
        }
        debouncing = false;
    }
#else
    // No debouncing - direct copy
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (current_matrix[i] != raw_matrix[i]) {
            current_matrix[i] = raw_matrix[i];
            changed = true;
        }
    }
#endif

    // Copy final matrix state
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        current_matrix[i] = matrix[i];
    }
    
    matrix_scan_kb();
    return changed;
}