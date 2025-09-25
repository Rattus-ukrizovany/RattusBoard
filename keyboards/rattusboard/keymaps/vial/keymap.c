// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Keymap converted from ZMK corne-zmk-config 
// Original: https://github.com/Rattus-ukrizovany/corne-zmk-config

#include QMK_KEYBOARD_H

/*
 * Layer definitions - matching original ZMK structure
 */
enum layers {
    _DEFAULT = 0,  // DEFAULT_L - Base QWERTY layer
    _SYMBOLS = 1,  // SYMBOLS_L - Numbers and symbols (was lower)
    _ARROWS = 2,   // ARROWS_L - F-keys, media, arrows (was raise)  
    _NUMBERS = 3,  // NUMBERS_L - Additional number layer
    _ADJUST = 4    // Flash layer - system controls (conditional)
};

/*
 * Custom keycodes
 */
enum custom_keycodes {
    SYMBOLS = SAFE_RANGE,
    ARROWS,
    ADJUST
};

/*
 * Keymap definition - Converted from ZMK corne-zmk-config
 * 
 * Base Layer (QWERTY) - Matches ZMK default_layer:
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │ TAB │  Q  │  W  │  E  │  R  │  T  │   │  Y  │  U  │  I  │  O  │  P  │BSPC │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │LSFT │  A  │  S  │  D  │  F  │  G  │   │  H  │  J  │  K  │  L  │  ;  │  '  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │LCTL │  Z  │  X  │  C  │  V  │  B  │   │  N  │  M  │  ,  │  .  │  /  │ ESC │
 * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
 *                   │ GUI │SYMB │ SPC │   │LT(3,│ARWS │ ALT │
 *                   └─────┴─────┴─────┘   │ENT) │     │     │
 *                                         └─────┴─────┴─────┘
 *                                         Trackball  Encoder (Scroll)
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer (DEFAULT_L from ZMK)
     */
    [_DEFAULT] = LAYOUT_split_3x6_3(
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
       KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
       KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ESC,
                                  KC_LGUI, SYMBOLS, KC_SPC,                    LT(_NUMBERS, KC_ENT), ARROWS,  KC_RALT
    ),

    /*
     * Symbols Layer (SYMBOLS_L from ZMK - was lower_layer)
     */
    [_SYMBOLS] = LAYOUT_split_3x6_3(
       KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
       KC_NO,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
       QK_BOOT, QK_BOOT, QK_BOOT, KC_CAPS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, QK_BOOT,
                                  KC_LGUI, KC_TRNS, KC_SPC,                             KC_ENT,  KC_TRNS, KC_RALT
    ),

    /*
     * Arrows Layer (ARROWS_L from ZMK - was raise_layer)  
     */
    [_ARROWS] = LAYOUT_split_3x6_3(
       KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_LCTL, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, QK_BOOT, QK_BOOT,
       KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_NO,   KC_MINS, KC_VOLD, KC_VOLU, KC_PIPE, KC_TILD,
                                  KC_LGUI, KC_TRNS, KC_SPC,                             KC_ENT,  KC_TRNS, KC_RALT
    ),

    /*
     * Numbers Layer (NUMBERS_L from ZMK - accessed via LT on Enter)
     */
    [_NUMBERS] = LAYOUT_split_3x6_3(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /*
     * Adjust Layer (Flash from ZMK - system controls, trackball, mouse)
     */
    [_ADJUST] = LAYOUT_split_3x6_3(
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, XXXXXXX, XXXXXXX, XXXXXXX,
                                  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS
    )
};

/*
 * Encoder map for scroll wheel functionality
 */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DEFAULT] = { ENCODER_CCW_CW(QK_MOUSE_WHEEL_UP, QK_MOUSE_WHEEL_DOWN) },       // Base: scroll wheel
    [_SYMBOLS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },                             // Symbols: volume
    [_ARROWS]  = { ENCODER_CCW_CW(QK_MOUSE_WHEEL_LEFT, QK_MOUSE_WHEEL_RIGHT) },   // Arrows: horizontal scroll
    [_NUMBERS] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },                             // Numbers: page up/down
    [_ADJUST]  = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },                             // Adjust: brightness
};
#endif

/*
 * Layer handling - updated for new layer names and ZMK-style activation
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYMBOLS:
            if (record->event.pressed) {
                layer_on(_SYMBOLS);
                update_tri_layer(_SYMBOLS, _ARROWS, _ADJUST);
            } else {
                layer_off(_SYMBOLS);
                update_tri_layer(_SYMBOLS, _ARROWS, _ADJUST);
            }
            return false;
            
        case ARROWS:
            if (record->event.pressed) {
                layer_on(_ARROWS);
                update_tri_layer(_SYMBOLS, _ARROWS, _ADJUST);
            } else {
                layer_off(_ARROWS);
                update_tri_layer(_SYMBOLS, _ARROWS, _ADJUST);
            }
            return false;
            
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
    }
    return true;
}
