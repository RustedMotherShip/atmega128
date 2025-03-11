#include "addr_led_lib.h"

void addr_led_write_one_byte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++) {
        if (byte & (1 << (7 - i))) 
        {
            // Отправка 1
            PORTA |= (1 << PD0); // Устанавливаем высокий уровень
            _delay_us(0.7); // Длительность высокого уровня
            PORTA &= (0 << PD0); // Устанавливаем низкий уровень
            _delay_us(0.6); // Длительность низкого уровня
        }
        else
        {
            // Отправка 0
            PORTA |= (1 << PD0); // Устанавливаем высокий уровень
            _delay_us(0.35); // Длительность высокого уровня
            PORTA &= (0 << PD0); // Устанавливаем низкий уровень
            _delay_us(0.8); // Длительность низкого уровня
        }
    }
}

void addr_led_write_parameters(params_t *values)
{
	uint8_t led_buffer[48] = {0};
    for (uint8_t i = 0; i < 15; i++)
    {
        if ((values->current_first <= values->current_second && i >= values->current_first && i <= values->current_second) || (values->current_first > values->current_second && (i >= first || i <= values->current_second))) 
        {
            led_buffer[i+i*0] = 255;
            led_buffer[i+i*1] = 0;
            led_buffer[i+i*2] = 0;
        } 
        else 
        {
            led_buffer[i+i*0] = 0;
            led_buffer[i+i*1] = 0;
            led_buffer[i+i*2] = 0;
        }
        
    }

    for(uint8_t i = 0; i < 48; i++)
    	addr_led_write_one_byte(led_buffer[i]);
    _delay_us(50);
}

