#ifndef UART_LIB_H
#define UART_LIB_H

#include <avr/io.h>
#include <stdint.h>

void uart_init(int baudrate);
void uart_write_byte(uint8_t data);
uint8_t uart_read_byte(void);
void uart_write(uint8_t *data, uint16_t length);
//void uart_read(uint8_t *data, uint16_t length)

#endif