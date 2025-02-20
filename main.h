#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <stdint.h>
#include <string.h>
#include <util/delay.h>
#include "libs/uart_lib.h"
#include "libs/i2c_lib.h"
#include "libs/ssd1306_lib.h"

#define I2C_DISPLAY_ADDR 0x3C
#define I2C_GY_302_ADDR 0x68

#endif
