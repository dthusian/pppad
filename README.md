# pppad/2k

![pppad/2k](https://i.imgur.com/jk1DIM4.jpeg!)

*Rapid trigger keypad for OSU!*
*Uses a rp2040 microcontroller with hall effect sensors*

* PCB files found in ./keypad
* Requires a magnet attached to the switch stem

## QMK Build instructions

Make example for this keyboard *(after setting up your build environment)*:

    make pppad/2k:default

Flashing example for this keyboard:

    make pppad/2k:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
