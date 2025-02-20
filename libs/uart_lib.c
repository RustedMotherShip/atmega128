#include "uart_lib.h"

void uart_init(int baudrate)
{
    UBRR0H = (uint8_t)(baudrate >> 8);
    UBRR0L = (uint8_t)baudrate;

    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_write_byte(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

uint8_t uart_read_byte(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void uart_write(uint8_t *data, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        uart_write_byte(data[i]);
    }
}

void uart_read(uint8_t *data, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        data[i] = uart_read_byte();
    }
}
