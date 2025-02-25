#include "joystick_lib.h"

void joystick_init(void) {
    // Настройка порта D как вход
    DDRD = 0x00; // Все пины порта D на вход

    cli();

	EIMSK |= (1 << INT2); 
	EIFR |= (1 << INT2); 
    // Настройка триггеров прерываний
    EICRA |= (0 << ISC21) | (0 << ISC20); // Прерывание по любому изменению на INT0 и INT1

    sei();
}

uint8_t check_axis_x(void)
{
	uint8_t x = adc_read(1);

	if(x > 136)
		return up;
	if(x < 120)
		return down;
	return zero;
}

uint8_t check_axis_y(void)
{
	uint8_t y = adc_read(0);

	if(y > 136)
		return up;
	if(y < 120)
		return down;
	return zero;
}