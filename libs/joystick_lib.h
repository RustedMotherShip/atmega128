#ifndef JOYSTICK_LIB_H
#define JOYSTICK_LIB_H

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "../libs/adc_lib.h"

#define zero 0
#define up 1
#define down 2
#define left 3
#define right 4

int8_t check_axis_x(void);
uint8_t check_axis_y(void);
void joystick_init(void);

#endif