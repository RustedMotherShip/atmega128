#include "joystick_lib.h"

uint8_t check_axis(void)
{
	uint8_t x = adc_read(0);
	uint8_t y = adc_read(1);

	if(y > 250)
		return up;
	if(y < 5)
		return down;
	if(x > 250)
		return right;
	if(x < 5)
		return left;
	
	return zero;
}