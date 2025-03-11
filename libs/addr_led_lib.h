#ifndef ADDR_LED_LIB_H
#define ADDR_LED_LIB_H

#include <avr/io.h>
#include "../libs/menu_lib.h"

void addr_led_write_parameters(params_t *values);
void addr_led_write_one_byte(uint8_t byte);

#endif