#include QMK_KEYBOARD_H
#include "custom_key_behavior.h"
#include "layers.h"
#include "custom_keycodes.h"

void handle_layer_activation(uint16_t layer, keyrecord_t *record) {
    static uint16_t tap_timer;
    static bool is_lower_held = false;
    static bool is_raise_held = false;
    static bool is_single_tap = false;
    static bool is_layer_toggled = false;
    static uint16_t last_tapped_layer;

    void set_row_colors(uint8_t colors[][3]) {
        // Define arrays for each row's LED indices
        uint8_t row1[] = {0, 1, 2, 3, 4, 5, 34, 35, 36, 37, 38, 39};
        uint8_t row2[] = {6, 7, 8, 9, 10, 11, 40, 41, 42, 43, 44, 45};
        uint8_t row3[] = {12, 13, 14, 15, 16, 17, 46, 47, 48, 49, 50, 51};
        uint8_t row4[] = {18, 19, 20, 21, 22, 23, 52, 53, 54, 55, 56, 57};
        uint8_t row5[] = {24, 25, 26, 27, 58, 59, 60, 61};

        // Array of pointers to each row array
        uint8_t* rows[] = {row1, row2, row3, row4, row5};
        // Array of sizes for each row array
        uint8_t sizes[] = {sizeof(row1)/sizeof(row1[0]), sizeof(row2)/sizeof(row2[0]), sizeof(row3)/sizeof(row3[0]),
                           sizeof(row4)/sizeof(row4[0]), sizeof(row5)/sizeof(row5[0])};
        const uint8_t num_rows = 5;

        // Iterate through each row
        for (uint8_t row = 0; row < num_rows; row++) {
            // Iterate through each LED in the current row
            for (uint8_t i = 0; i < sizes[row]; i++) {
                // Set color for this LED
                rgb_matrix_set_color(rows[row][i], colors[row][0], colors[row][1], colors[row][2]);
            }
        }
    }

    void update_layer_states(bool is_raise_held, bool is_lower_held) {
        if (is_raise_held && is_lower_held) {
            layer_off(_RAISE);
            layer_off(_LOWER);
            layer_on(_ADJUST);
            // rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_color_all(10, 10, 50);
        } else if (is_raise_held) {
            layer_on(_RAISE);

            uint8_t custom_colors[5][3] = {
                {30, 0, 0},  // Red for row 1
                {0, 30, 0},  // Green for row 2
                {0, 0, 30},  // Blue for row 3
                {30, 30, 0}, // Yellow for row 4
                {0, 30, 30}  // Cyan for row 5
            };

            set_row_colors(custom_colors);
        } else if (is_lower_held) {
            layer_on(_LOWER);
            rgb_matrix_set_color_all(0, 0, 100);
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

