#pragma once

enum custom_keycodes {
    RALT_RGUI = SAFE_RANGE,
    LGUI_LALT
};

// Special
#define ENT_LWR LT(_LOWER,KC_ENT)
#define CTL_ESC LCTL_T(KC_ESC)
#define SFT_SPC MT(MOD_LSFT,KC_SPC)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RSFT OSM(MOD_RSFT)

// Faster deletion
#define ALT_BSPC LALT(KC_BSPC)
#define ALT_DEL LALT(KC_DEL)
#define GUI_BSPC LGUI(KC_BSPC)
#define GUI_DEL LGUI(KC_DEL)

// Faster navigation
#define ALT_LEFT LALT(KC_LEFT)
#define ALT_DOWN LALT(KC_DOWN)
#define ALT_UP LALT(KC_UP)
#define ALT_RGHT LALT(KC_RGHT)

// Homerow mods
#define LALT_A LALT_T(KC_A)
#define LSFT_S LSFT_T(KC_S)
#define LCTL_D LCTL_T(KC_D)
#define LGUI_F LGUI_T(KC_F)
#define RGUI_J RGUI_T(KC_J)
#define RCTL_K RCTL_T(KC_K)
#define RSFT_L RSFT_T(KC_L)
#define RALT_SC RALT_T(KC_SCLN)
#define LSFT_PLS LSFT_T(KC_PPLS)
#define LALT_P4 LALT_T(KC_P4)
#define LCTL_P5 LCTL_T(KC_P5)
#define LGUI_P6 LGUI_T(KC_P6)
