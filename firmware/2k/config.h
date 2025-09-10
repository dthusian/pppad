// Copyright 2023 Peter Zhou (@GodlyPeeta)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <math.h>
#pragma once

#define MATRIX_ROWS 2
#define MATRIX_COLS 2

#define ANALOG_PINS {GP26, GP27}

#define AVERAGE_SIZE_SQRT 5
#define AVERAGE_SIZE (1 << AVERAGE_SIZE_SQRT)

#define DEBUG_MATRIX_SCAN_RATE

// #define RGB_DI_PIN GP17
// #define RGBLED_NUM 8

// #define RGBLIGHT_EFFECT_RGB_TEST        
// #define WS2812_PIO_USE_PIO1 


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
