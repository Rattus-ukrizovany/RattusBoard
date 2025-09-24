// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include "matrix.h"
#include "quantum.h"
#include "debug.h"
#include "split_common/split_util.h"

/*
 * Custom matrix implementation for RattusBoard
 * 
 * This implements the 6x7 matrix scanning for the split keyboard.
 * The matrix is organized as:
 * - 6 columns total (3 per half)
 * - 7 rows total (shared between halves)
 * - Diodes are COL2ROW
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
    
    // Determine which columns to scan based on split half
    uint8_t col_start, col_end;
    if (isLeftHand) {
        col_start = MATRIX_COLS / 2;
        col_end = MATRIX_COLS;      // Scan columns 3-5 for left half (slave)
    } else {
        col_start = 0;
        col_end = MATRIX_COLS / 2;  // Scan columns 0-2 for right half (master)
    }
    
    // Scan the matrix
    for (uint8_t col = col_start; col < col_end; col++) {
        // Select column
        writePinLow(col_pins[col]);
        
        // Small delay for signal to propagate
        matrix_io_delay();
        
        // Read all rows for this column
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

void matrix_init(void) {
    matrix_init_custom();
}

uint8_t matrix_scan(void) {
    bool changed = matrix_scan_custom(matrix);
    return (uint8_t)changed;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}