#include QMK_KEYBOARD_H
// #include "print.h"

enum custom_layers {
    _DEFAULT,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    OSM_RALT_RGUI = SAFE_RANGE,
    OSM_LGUI_LALT
};

// SP_ecial keys for conciseness
#define SP_CESC LCTL_T(KC_ESC)
#define SP_SSPC MT(MOD_LSFT,KC_SPC)
#define SP_CQUOT MT(MOD_RCTL,KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
        SP_CESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, SP_CQUOT,
        OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_DEL, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT),
        OSM_LGUI_LALT, _LOWER, SP_SSPC, SC_SENT, _RAISE, OSM_RALT_RGUI
    ),

    [_LOWER] = LAYOUT(
        QK_BOOT, KC_PAST, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_WH_U, KC_WH_D, KC_BTN2, KC_PGUP, KC_HOME,
        KC_NO, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_COMM, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_PGDN, KC_END,
        KC_NO, KC_PPLS, KC_P4, KC_P5, KC_P6, KC_PDOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DEL, KC_BSPC,
        KC_NO, KC_PMNS, KC_P1, KC_P2, KC_P3, KC_P0, KC_NO, LALT(KC_BSPC), LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP), LALT(KC_RGHT), KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS
    ),

    [_RAISE] = LAYOUT(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, KC_QUES, KC_TRNS,
        KC_TRNS, KC_LCBR, KC_LBRC, KC_LPRN, KC_MINS, KC_UNDS, KC_PLUS, KC_PEQL, KC_RPRN, KC_RBRC, KC_RCBR, KC_TRNS,
        KC_TRNS, KC_LT, KC_SLSH, KC_QUOT, KC_DQUO, KC_GRV, LALT(KC_DEL), KC_TRNS, KC_PIPE, KC_SCLN, KC_COLN, KC_BSLS, KC_GT, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_ADJUST] = LAYOUT(
        QK_BOOT, KC_NO, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU,
        KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT,
        KC_NO, KC_NO, KC_F4, KC_F5, KC_F6, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
        KC_SLEP, KC_NO, KC_F1, KC_F2, KC_F3, KC_NO, LGUI(KC_DEL), LGUI(KC_BSPC), RGB_M_P, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

// Function to handle the one-shot and swapping behavior of modifiers
void handle_mod_swap_oneshot(uint16_t mod_primary, uint16_t mod_secondary, keyrecord_t *record) {
    static uint16_t osm_timer;  // Timer to track tap intervals
    static bool is_single_tap = false;  // State to track if the first tap has occurred

    if (record->event.pressed) {
        if (is_single_tap && timer_elapsed(osm_timer) < TAPPING_TERM) {
            // Swap the modifiers on a double tap
            unregister_mods(MOD_BIT(mod_primary));
            set_oneshot_mods(MOD_BIT(mod_secondary));
            is_single_tap = false; // Reset the tap state
            return;
        }
        // Start timer on the first press
        osm_timer = timer_read();
        register_mods(MOD_BIT(mod_primary)); // Act as if the primary modifier is held down
        is_single_tap = true; // Mark as a possible single tap
    } else {
        // On key release, handle the one-shot or end the hold
        unregister_mods(MOD_BIT(mod_primary));
        if (is_single_tap && timer_elapsed(osm_timer) < TAPPING_TERM) {
            set_oneshot_mods(MOD_BIT(mod_primary));
        }
    }
}

// Function to handle one-shot and holding behavior or layer keys
void handle_layer_tap(uint16_t layer, keyrecord_t *record) {
    static uint16_t layer_timer;  // Timer to track tap intervals

    if (record->event.pressed) {
        // On key press activate the layer
        layer_timer = timer_read();
        layer_on(layer);
    } else {
        // On key release, handle the one-shot or end the hold
        layer_off(layer);
        if (timer_elapsed(layer_timer) < TAPPING_TERM) {
            set_oneshot_layer(layer, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
    }
}

// Activate _ADJUST layer when holding both layer keys
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Apply custom behavior
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM_RALT_RGUI:
            handle_mod_swap_oneshot(KC_RALT, KC_RGUI, record);
            return false;
        case OSM_LGUI_LALT:
            handle_mod_swap_oneshot(KC_RGUI, KC_RALT, record);
            return false;
        case _LOWER:
            handle_layer_tap(_LOWER, record);
            return false;
        case _RAISE:
            handle_layer_tap(_RAISE, record);
            return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
}


