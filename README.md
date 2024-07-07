# qmk-keymap

This repo works as an [External QMK Userspace](https://docs.qmk.fm/newbs_external_userspace).

It contains my custom keymap config for my [Iris CE](https://keeb.io/products/iris-ce-keyboard) split keyboard.

## Keymap Philosophy

- **Efficient Modifier Use**: Avoid using layer or modifier keys on the same half as the primary key.
- **Dynamic Layers & Modifiers**:
  - Modifiers and layers are primarily one-shot but can also function normally when held.
  - Holding both shift keys activates "[Caps Word](https://docs.qmk.fm/features/caps_word#caps-word)"
- **LED Indicators**: LEDs show active layers or mods.

## Layers

- **DEFAULT**: Standard QWERTY layout.
- **LOWER**: Features Vim-style navigation on the right, with a numpad on the left half.
- **RAISE**: Dedicated symbols layer.
- **ADJUST**: Includes function keys (F1-F12), media controls, and RGB settings.

## Layer Activation Logic

- **Hold**: Activates the layer until released.
- **Tap**: Registers as a one-shot layer for the next keypress.
- **Double-Tap**: Locks the layer until tapped again.
- **Both Layer Keys Held**: Activates the ADJUST layer until both are released.

## Custom Key Behavior

- **CMD/ALT Swaping**:
  - **Hold CMD/ALT**: Functions as the respective modifier.
  - **Tap CMD/ALT**: Acts as a one-shot modifier.
  - **Double-Tap CMD/ALT**: Registers a one-shot of the opposite modifier (CMD ↔ ALT).

## RGB LED Layer Indicators

- **Active Layer Highlighting**: Only keys configured per active layer are illuminated.
- **Color Customization**: Each layer is represented by a unique color, toggleable with the custom keycode `RGB_LYRS`.
- **DEFAULT Layer**: RGB effects and colors can be adjusted in the ADJUST layer.

## Installation

Here's how to use it in QMK:

1. [Set up QMK](https://docs.qmk.fm/newbs).

2. Clone this repo locally

   ```sh
   git clone https://github.com/hendrikmi/qmk-keymap
   ```

3. Set global userspace path, replacing "`path/to/qmk-keymap`" with the relative path to your clone of `qmk-keymap` from the previous step:

   ```sh
   qmk config user.overlay_dir="$(realpath path/to/qmk-keymap)"
   ```

4. Put keyboard into [bootloader mode](https://docs.qmk.fm/newbs_flashing#put-your-keyboard-into-dfu-bootloader-mode)

5. Flash my keymap with

   ```sh
   qmk flash -kb keebio/iris_ce/rev1 -km hendrikmi
   ```
