#include QMK_KEYBOARD_H
#include "config.h"
#include "custom_key_behavior.h"
#include "sync.h"
// #include "printf.h"

#ifdef RGB_MATRIX_ENABLE
/**
 * Sets the color of a specific LED in the RGB matrix based on a specified hue.
 * Retrieves the current HSV color settings, updates the hue while keeping the 
 * saturation and value unchanged, then converts the updated HSV color 
 * to RGB format and applies it to the LED at the specified index.
 */
void rgb_matrix_set_color_hue(uint8_t index, uint8_t hue) {
    HSV hsv = rgb_matrix_get_hsv();
    hsv.h = hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Skip LED activation if it is disabled
    if (!user_state.custom_rgb_layers_enabled){
        return false;
    }

    // uint8_t layer = get_highest_layer(layer_state|default_layer_state);
    uint8_t layer = get_highest_layer(layer_state);
    static uint32_t layer_activation_time = 0;
    static uint8_t last_layer = 0;

    // Check if the layer has changed or just activated
    if (layer != last_layer) {
        // uprintf("layer: %d - last_layer: %d\n", layer, last_layer);
        layer_activation_time = timer_read();  // Reset timer at layer change
        last_layer = layer;
    }

    // Only activate layer effects if the layer has been active for more than LAYER_LED_ACTIVATION_TIME 
    if (layer > 0 && timer_elapsed(layer_activation_time) > LAYER_LED_ACTIVATION_TIME) {
        uint8_t hue;
        switch (layer) {
            /*
            hue = 168; // blue
            hue = 80; // green
            hue = 128; // cyan
            hue = 0; // red
            hue = 40; // yellow
            hue = 232; // pink
            hue = 176; // purple
            */
            case 1: // LOWER layer
                hue = 80; // green
                break;
            case 2: // RAISE layer
                hue = 128; // cyan
                break;
            case 3: // ADJUST layer
                hue = 0; // red
                break;
            default:
                // Default color for other layers
                hue = 168; // blue
        }

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});
                    if (keycode > KC_TRNS) {
                        rgb_matrix_set_color_hue(index, hue); // Set the color for configured keys 
                    } else {
                        rgb_matrix_set_color(index, 0, 0, 0); // Turn off the LED for non-configured keys
                    }
                }
            }
        }
    }

    // Light modifiers when they are active
    if (user_state.caps_word_enabled || user_state.shift_mod_enabled) {
        rgb_matrix_set_color_hue(26, 0);
        rgb_matrix_set_color_hue(60, 0);
    } 
    if (user_state.alt_mod_enabled) {
        rgb_matrix_set_color_hue(63, 0);
    } 
    if (user_state.gui_mod_enabled) {
        rgb_matrix_set_color_hue(29, 0);
    } 
    if (user_state.ctrl_mod_enabled) {
        rgb_matrix_set_color_hue(15, 0);
    } 
    return false;
}

// Default matrix RGB effect
void matrix_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
    rgb_matrix_sethsv_noeeprom(110,255,120);
};
#endif
