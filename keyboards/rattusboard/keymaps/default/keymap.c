// Copyright 2024 RattusBoard Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

/*
 * Layer definitions
 */
enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

/*
 * Custom keycodes
 */
enum custom_keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
    ADJUST
};

/*
 * Keymap definition
 * 
 * Base Layer (QWERTY):
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  Q  │  W  │  E  │  R  │  T  │     │   │     │  Y  │  U  │  I  │  O  │  P  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │  A  │  S  │  D  │  F  │  G  │     │   │     │  H  │  J  │  K  │  L  │  ;  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │  Z  │  X  │  C  │  V  │  B  │     │   │     │  N  │  M  │  ,  │  .  │  /  │
 * └─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │ GUI │ SPC │LOWER│   │RAISE│ ENT │ ALT │
 *                   └─────┴─────┴─────┘   └─────┴─────┴─────┘
 *                                         Trackball  Encoder (Scroll)
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer
     */
    [_BASE] = LAYOUT_split_3x6_3(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,                            XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,                            XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,                            XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ESC,  KC_TAB,  KC_LGUI,                                                                          KC_RALT, KC_BSPC, KC_DEL,
    //└────────┴────────┴────────┘                                                      └────────┴────────┴────────┘
                                    KC_LGUI, KC_SPC,  LOWER,                            RAISE,   KC_ENT,  KC_RALT
    //                              └────────┴────────┴────────┘                        └────────┴────────┴────────┘
    ),

    /*
     * Lower Layer (Numbers, F-keys, Navigation)
     */
    [_LOWER] = LAYOUT_split_3x6_3(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,                            XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,                            XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_F11,  KC_F12,  TB_TOG,  TB_DPI_DN,TB_DPI_UP,XXXXXXX,                          XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ESC,  KC_TAB,  KC_LGUI,                                                                          KC_RALT, KC_BSPC, KC_DEL,
    //└────────┴────────┴────────┘                                                      └────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, KC_TRNS,                          ADJUST,  KC_TRNS, KC_TRNS
    //                              └────────┴────────┴────────┘                        └────────┴────────┴────────┘
    ),

    /*
     * Raise Layer (Symbols, Media)
     */
    [_RAISE] = LAYOUT_split_3x6_3(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,                            XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX,                            XXXXXXX, KC_QUOT, KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, XXXXXXX,                            XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ESC,  KC_TAB,  KC_LGUI,                                                                          KC_RALT, KC_BSPC, KC_DEL,
    //└────────┴────────┴────────┘                                                      └────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, ADJUST,                           KC_TRNS, KC_TRNS, KC_TRNS
    //                              └────────┴────────┴────────┘                        └────────┴────────┴────────┘
    ),

    /*
     * Adjust Layer (System, Mouse, RGB)
     */
    [_ADJUST] = LAYOUT_split_3x6_3(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ESC,  KC_TAB,  KC_LGUI,                                                                          KC_RALT, KC_BSPC, KC_DEL,
    //└────────┴────────┴────────┘                                                      └────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS
    //                              └────────┴────────┴────────┘                        └────────┴────────┴────────┘
    )
};

/*
 * Encoder map for scroll wheel functionality
 */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },    // Base: scroll wheel
    [_LOWER]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },              // Lower: volume
    [_RAISE]  = { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) }, // Raise: horizontal scroll
    [_ADJUST] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },              // Adjust: brightness
};
#endif

/*
 * Layer handling
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
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