/**
 * Manages synchronization of runtime configuration states across split keyboard halves.
 * This file uses QMK's transactions framework to facilitate communication between halves.
 *
 * Types:
 * - `user_runtime_config_t`: A union for storing and accessing configuration states as
 *   a compact uint32_t or individual bits. Mainly used to track the activation state of 
 *   custom RGB layers.
 *
 * Globals:
 * - `user_state`: An extern declaration of `user_runtime_config_t` to share state across
 *   different parts of the firmware.
 *
 * Usage:
 * Include this file in modules where synchronization of keyboard halves is required.
 * Define `user_state` in one source file to ensure a single instantiation.
 */
#pragma once

typedef union {
    uint32_t raw;
    struct {
        bool custom_rgb_layers_enabled :1; // Global flag indicating if custom RGB layers are activated
        bool caps_word_enabled :1;
        bool shift_mod_enabled :1;
        bool alt_mod_enabled :1;
        bool gui_mod_enabled :1;
        bool ctrl_mod_enabled :1;
    };
} user_runtime_config_t;

extern user_runtime_config_t user_state;

