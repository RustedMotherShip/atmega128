#include "addr_led_lib.h"

void addr_led_write_parameters(params_t *values)
{
	uint8_t led_buffer[48] = {0};
    for (uint8_t i = 0; i < 16; i++)
    {
        if ((values->current_first <= values->current_second && i >= values->current_first && i <= values->current_second) || (values->current_first > values->current_second && (i >= first || i <= values->current_second))) 
        {
            // Заполняем цветами
            led_buffer[i * 3] = values -> current_green; // Зеленый
            led_buffer[i * 3 + 1] = values -> current_red; // Красный
            led_buffer[i * 3 + 2] = values -> current_blue; // Синий
        } 
        else 
        {
            // Заполняем черным цветом
            led_buffer[i * 3] = 0x00;
            led_buffer[i * 3 + 1] = 0x00;
            led_buffer[i * 3 + 2] = 0x00;
        }
        
    }

    for(uint8_t curr_byte_i = 0; curr_byte_i < 48; curr_byte_i++)
    {
        for (uint8_t i = 0; i < 8; i++) 
        {
            if (led_buffer[curr_byte_i] & (1 << (7 - i))) 
            {
                // Отправка 1
                PORTA += 1; // Устанавливаем высокий уровень
                __asm__("nop");// Длительность высокого уровня
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                PORTA = 0; // Устанавливаем низкий уровень
            }
            else
            {
                // Отправка 0
                PORTA = 0x01; // Устанавливаем высокий уровень
                PORTA = 0; // Устанавливаем низкий уровень
                __asm__("nop");// Длительность низкого уровня
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
                __asm__("nop");
            }
        }
    }
    _delay_us(50);
}

