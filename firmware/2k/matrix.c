
#include QMK_KEYBOARD_H
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "analog.h"
#include "print.h"
#include "config.h"

#define testnum 32000

typedef struct {
    int16_t val;
    int16_t avrg;
    int16_t local_min;
    int16_t local_max;

    int16_t pin;

    int16_t avrg_arr[AVERAGE_SIZE];
    int16_t avrg_sum;
    int16_t avrg_pointer;
} key_analog;

static key_analog analog_keys[MATRIX_COLS];

static int16_t actuation_down = 50;
static int16_t actuation_up = 50;

void matrix_init_custom(void) {
    int16_t temp[] = ANALOG_PINS;

    for (int16_t i = 0; i < MATRIX_COLS; i++) {
        analog_keys[i].local_max = 0;
        analog_keys[i].local_min = 9999;
        analog_keys[i].val = 0;

        analog_keys[i].pin = temp[i];
    }
}

static uint16_t key_timer = 0;
static uint16_t pissi = 0; 

static uint16_t pissarr[testnum];
static uint16_t pissavg[testnum];
static uint16_t debug_timer = 0;

static bool flag = false;
static uint16_t arrss[testnum];
static uint16_t arrss2[testnum];
static uint16_t incr = 0;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    matrix_row_t last_matrix = current_matrix[0];

    key_timer = timer_read();

    for (int16_t i = 0; i < MATRIX_COLS; i++) {
        analog_keys[i].val = analogReadPin(analog_keys[i].pin);

        // rolling average stuff
        // update rolling sum 
        analog_keys[i].avrg_sum += analog_keys[i].val - analog_keys[i].avrg_arr[analog_keys[i].avrg_pointer];
        // update rolling array
        analog_keys[i].avrg_arr[analog_keys[i].avrg_pointer] = analog_keys[i].val;
        // update the actual average
        analog_keys[i].avrg = analog_keys[i].avrg_sum >> AVERAGE_SIZE_SQRT;
        // update the pointer 
        analog_keys[i].avrg_pointer = (analog_keys[i].avrg_pointer + 1) % AVERAGE_SIZE;

        if (key_timer < 500) continue;

        if (analog_keys[i].avrg < analog_keys[i].local_min) {
            analog_keys[i].local_min = analog_keys[i].avrg;
            if (i == 0) flag = true;
        }
        if (analog_keys[i].avrg > analog_keys[i].local_max) {
            analog_keys[i].local_max = analog_keys[i].avrg;
            if (i == 0) flag = true;
        }
        
        if (key_timer < 1000) continue;

        if (analog_keys[i].local_min - analog_keys[i].val <= -actuation_down) {
            current_matrix[0] |= 1 << i;  
            analog_keys[i].local_max = analog_keys[i].val;
        } 
        if (analog_keys[i].local_max - analog_keys[i].val >= actuation_up) {
            current_matrix[0] &= ~(1 << i);
            analog_keys[i].local_min = analog_keys[i].val;
        }

        if (key_timer - debug_timer > 300) {
            uprintf("debug tick \n");
            for (int16_t i = 0; i < MATRIX_COLS; i++) {
                uprintf("Key %d: %d [MIN: %d, MAX: %d] AVRG: %d SUM: %d \n", i, analog_keys[i].val, analog_keys[i].local_min, analog_keys[i].local_max, analog_keys[i].avrg, analog_keys[i].avrg_sum);
            }

            if (flag) {
                for (int16_t i = 0; i < incr; i++) {
                    uprintf("%d ", arrss[i]);
                }
                uprintf("\n second \n");
                for (int16_t i = 0; i < incr; i++) {
                    uprintf("%d ", arrss2[i]);
                }
                uprintf("\n");
                
            }

            flag = false;
            incr = -1; 

            debug_timer = key_timer;
        }
    }

    arrss[incr] = analog_keys[0].avrg;
    arrss2[incr] = analog_keys[0].val;
    incr ++;


    pissarr[pissi] = analog_keys[0].val;
    pissavg[pissi] = analog_keys[0].avrg;
    pissi++;

    // if (pissi == testnum) {
    //     pissi = 0;
    //     for (uint16_t i = 0; i < testnum; i++) {
    //         uprintf("%d ", pissarr[i]);
    //     }
    //     uprintf("second\n");
    //     for (uint16_t i = 0; i < testnum; i++) {
    //         uprintf("%d ", pissavg[i]);
    //     }
    //     uprintf("\n");

    // }

    

    // get values from adc
    

    if (last_matrix != current_matrix[0]) {
        matrix_has_changed = true;
    }

    

    // debuggggggg
    // uprint("tick\n");


    return matrix_has_changed;
}