#include QMK_KEYBOARD_H
#include "custom_key_behavior.h"
#include "layers.h"
#include "custom_keycodes.h"
#include "sync.h"

void handle_mod_swap_oneshot(uint16_t mod_primary, uint16_t mod_secondary, keyrecord_t *record) {
    static uint16_t osm_timer;  // Timer to track tap intervals
    static bool is_single_tap = false;  // State to track if the first tap has occurred

    if (record->event.pressed) {
        if (is_single_tap && timer_elapsed(osm_timer) < TAPPING_TERM) {
            // Swap the modifiers on a double tap
            unregister_mods(MOD_BIT(mod_primary));
            set_oneshot_mods(MOD_BIT(mod_secondary));
            is_single_tap = false;
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

// Apply custom key behavior
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // HSV hsv = rgb_matrix_get_hsv();
    // uprintf("Current HSV - H: %d S: %d V: %d\n", hsv.h, hsv.s, hsv.v);

    switch (keycode) {
        case RALT_RGUI:
            handle_mod_swap_oneshot(KC_RALT, KC_RGUI, record);
            return false;
        case LGUI_LALT:
            handle_mod_swap_oneshot(KC_RGUI, KC_RALT, record);
            return false;
        case RGB_LYRS:
            if (record->event.pressed) {
                // Toggle state of the custom RGB light layers
                user_state.custom_rgb_layers_enabled = !user_state.custom_rgb_layers_enabled;
            }
            return false;
    }
    return true;
}
