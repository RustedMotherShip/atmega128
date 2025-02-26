#ifndef I2C_LIB_H
#define I2C_LIB_H

#include <avr/io.h>
#include <util/twi.h>
#include <stdint.h>
#include <avr/interrupt.h>

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_send_address(uint8_t address, uint8_t rw_type);
uint8_t i2c_read_byte(void);
void i2c_read(uint8_t dev_addr, uint8_t size, uint8_t *data);
uint8_t i2c_send_byte(uint8_t data);
void i2c_write(uint8_t dev_addr, uint8_t size, uint8_t *data);

#endif