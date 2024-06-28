# qmk-keymap

My keymap config for QMK

## Installation

This repo works as an [External QMK Userspace](https://docs.qmk.fm/newbs_external_userspace).

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
