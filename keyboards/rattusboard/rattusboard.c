// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include "rattusboard.h"

/*
 * Trackball state and configuration
 */
static bool trackball_scroll_mode = false;
static uint16_t trackball_dpi = 1600;

/*
 * Custom keycode processing
 */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case TB_TOG:
            if (record->event.pressed) {
                trackball_scroll_mode = !trackball_scroll_mode;
            }
            return false;
            
        case TB_DPI_UP:
            if (record->event.pressed) {
                if (trackball_dpi < 12000) {
                    trackball_dpi += 400;
                    pointing_device_set_cpi(trackball_dpi);
                }
            }
            return false;
            
        case TB_DPI_DN:
            if (record->event.pressed) {
                if (trackball_dpi > 400) {
                    trackball_dpi -= 400;
                    pointing_device_set_cpi(trackball_dpi);
                }
            }
            return false;
            
        case TB_RESET:
            if (record->event.pressed) {
                trackball_dpi = 1600;
                trackball_scroll_mode = false;
                pointing_device_set_cpi(trackball_dpi);
            }
            return false;
    }
    
    return true;
}

/*
 * Pointing device initialization
 */
void pointing_device_init_kb(void) {
    pointing_device_set_cpi(trackball_dpi);
    pointing_device_init_user();
}

/*
 * Pointing device task - handles trackball input
 */
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (trackball_scroll_mode) {
        // Convert X/Y movement to scroll wheel
        if (mouse_report.x != 0 || mouse_report.y != 0) {
            // Use X movement for horizontal scroll, Y for vertical
            mouse_report.h = mouse_report.x;
            mouse_report.v = -mouse_report.y;  // Invert Y for natural scrolling
            mouse_report.x = 0;
            mouse_report.y = 0;
        }
    }
    
    return pointing_device_task_user(mouse_report);
}

/*
 * Encoder mapping for scroll wheel functionality
 */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },  // Base layer: scroll wheel
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },            // Layer 1: volume control
    [2] = { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) }, // Layer 2: horizontal scroll
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },            // Layer 3: transparent
};
#endif

/*
 * Keyboard initialization
 */
void keyboard_post_init_kb(void) {
    // Set default trackball DPI
    pointing_device_set_cpi(trackball_dpi);
    
    keyboard_post_init_user();
}

/*
 * Layer state change handling
 */
layer_state_t layer_state_set_kb(layer_state_t state) {
    return layer_state_set_user(state);
}

/*
 * Split keyboard transport for sharing trackball state
 */
#ifdef SPLIT_KEYBOARD
typedef struct {
    bool trackball_scroll_mode;
    uint16_t trackball_dpi;
} user_runtime_config_t;

static user_runtime_config_t user_state;

void user_transport_update(void) {
    if (is_keyboard_master()) {
        user_state.trackball_scroll_mode = trackball_scroll_mode;
        user_state.trackball_dpi = trackball_dpi;
    }
}

void user_transport_sync(void) {
    if (!is_keyboard_master()) {
        trackball_scroll_mode = user_state.trackball_scroll_mode;
        trackball_dpi = user_state.trackball_dpi;
    }
}
#endif