#include QMK_KEYBOARD_H
#include "custom_key_behavior.h"
#include "layers.h"
#include "custom_keycodes.h"

/**
 * Handle layer activation:
 * - If a layer key is held:
 *     -> Activate the layer until the key is released.
 * - If a layer key is tapped:
 *     -> Register the layer as a one-shot layer, active for the next key press.
 * - If a layer key is double-tapped:
 *     -> Activate the layer and keep it active until the key is tapped again.
 * - If both layer keys (e.g., RAISE and LOWER) are held simultaneously:
 *     -> Activate the ADJUST layer until both keys are released.
 */
void handle_layer_activation(uint16_t layer, keyrecord_t *record) {
    static uint16_t tap_timer;
    static bool is_lower_held = false;
    static bool is_raise_held = false;
    static bool is_single_tap = false;
    static bool is_layer_toggled = false;
    static uint16_t last_tapped_layer;

    void update_layer_states(bool is_raise_held, bool is_lower_held) {
        if (is_raise_held && is_lower_held) {
            layer_off(_RAISE);
            layer_off(_LOWER);
            layer_on(_ADJUST);
        } else if (is_raise_held) {
            layer_on(_RAISE);
        } else if (is_lower_held) {
            layer_on(_LOWER);
        }
    }

    void deactivate_all_layers(void) {
        layer_off(_ADJUST);
        layer_off(_RAISE);
        layer_off(_LOWER);
    }

    if (record->event.pressed) {
        bool is_same_layer = (last_tapped_layer == layer);
        bool within_tap_term = (timer_elapsed(tap_timer) < TAPPING_TERM);
        bool not_adjust_layer = (layer != _ADJUST);

        if (is_single_tap && is_same_layer && within_tap_term && not_adjust_layer) {
            is_layer_toggled = true;
            is_single_tap = false;
            return;
        }

        if (layer == _RAISE) {
            is_raise_held = true;
        } else if (layer == _LOWER) {
            is_lower_held = true;
        }

        update_layer_states(is_raise_held, is_lower_held);
        tap_timer = timer_read();
        is_single_tap = true;
        last_tapped_layer = layer;
    } else {
        if (!is_single_tap) {
            layer_on(layer);
        } else {
            deactivate_all_layers();

            bool within_tap_term = (timer_elapsed(tap_timer) < TAPPING_TERM);
            if (within_tap_term && !is_layer_toggled) {
                set_oneshot_layer(layer, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            is_lower_held = false;
            is_raise_held = false;
            is_layer_toggled = false;
        }
    }
}

/**
 * Handle the one-shot and swapping behavior of modifiers:
 * - If CMD or ALT is held:
 *     -> Act as the respective modifier (CMD or ALT).
 * - If CMD or ALT is tapped:
 *     -> Register the key as a one-shot modifier, active for the next key press.
 * - If CMD or ALT is double-tapped:
 *     -> Register a one-shot modifier of the opposite modifier:
 *         - CMD double-tap registers a one-shot ALT.
 *         - ALT double-tap registers a one-shot CMD.
 */
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

// Apply custom key behavior
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RALT_RGUI:
            handle_mod_swap_oneshot(KC_RALT, KC_RGUI, record);
            return false;
        case LGUI_LALT:
            handle_mod_swap_oneshot(KC_RGUI, KC_RALT, record);
            return false;
        case _LOWER:
            handle_layer_activation(_LOWER, record);
            return false;
        case _RAISE:
            handle_layer_activation(_RAISE, record);
            return false;
    }
    return true;
}

