#include QMK_KEYBOARD_H
#include "config.h"
#include "layers.h"
#include "custom_keycodes.h"
// #include "light_layers.h"
#include "print.h"

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       CTL_ESC, LALT_A,  LSFT_S,  LCTL_D,  LGUI_F,  KC_G,                               KC_H,    RGUI_J,  RCTL_K,  RSFT_L,  RALT_SC, KC_QUOT,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       OSM_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,           KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSM_RSFT,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      LGUI_LALT,_LOWER, SFT_SPC,                   ENT_LWR, _RAISE,  RALT_RGUI 
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),

    [_LOWER] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       QK_BOOT, KC_PAST, KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_BTN1, KC_WH_U, KC_WH_D, KC_BTN2, KC_PGUP, KC_HOME,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO,   KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_COMM,                            KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_PGDN, KC_END,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO,   LSFT_PLS,LALT_P4, LCTL_P5, LGUI_P6, KC_PDOT,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_BSPC,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO,   KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_NO,            ALT_BSPC,ALT_LEFT,ALT_DOWN,ALT_UP,  ALT_RGHT,KC_NO,   KC_NO,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______, _______, _______,                   KC_BSPC, _______, _______ 
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),

    [_RAISE] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, KC_QUES, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, KC_LCBR, KC_LBRC, KC_LPRN, KC_MINS, KC_UNDS,                            KC_PLUS, KC_PEQL, KC_RPRN, KC_RBRC, KC_RCBR, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______, KC_LT,   KC_SLSH, KC_QUOT, KC_DQUO, KC_GRV,  ALT_DEL,          _______, KC_PIPE, KC_SCLN, KC_COLN, KC_BSLS, KC_GT,   _______,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______, _______, KC_DEL,                    _______, _______, _______ 
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),

    [_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       QK_BOOT, KC_NO,   KC_F10,  KC_F11,  KC_F12,  KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       QK_RBT,  KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       EE_CLR,  KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_NO,                              RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_SLEP, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_NO,   GUI_DEL,          GUI_BSPC,RGB_M_P, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    )
};

// clang-format on

void keyboard_post_init_user(void) {
  debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
}
// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     uprintf("led_min: %d - led_max: %d\n", led_min, led_max);
//
//     for (uint8_t i = led_min; i < led_max; i++) {
//         switch(get_highest_layer(layer_state|default_layer_state)) {
//             case 2:
//                 rgb_matrix_set_color(i, 0, 0, 120);
//                 break;
//             case 1:
//                 rgb_matrix_set_color(i, 0, 120, 0);
//                 break;
//             default:
//                 break;
//         }
//     }
//     return false;
// }
