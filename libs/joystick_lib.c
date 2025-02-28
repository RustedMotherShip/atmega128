#include "joystick_lib.h"

void joystick_init(void) {
    // Настройка порта D как вход
    DDRD = 0b11111011; // Все пины порта D на вход

    cli();

	EIMSK |= (1 << INT2); 
	EIFR |= (1 << INT2); 
    // Настройка триггеров прерываний
    EICRA |= (0 << ISC21) | (0 << ISC20); // Прерывание по любому изменению на INT0 и INT1

    sei();
}

int8_t check_axis_x(void)
{
	int8_t raw_x = adc_read(0);
	int8_t x = raw_x - 128;
	if(x > -8 || x < 8)
		return x;
	return zero;
	
}

uint8_t check_axis_y(void)
{
	uint8_t y = adc_read(1);

	if(y > 136)
		return up;
	if(y < 120)
		return down;
	return zero;
}