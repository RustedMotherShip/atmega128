#ifndef ADC_LIB_H
#define ADC_LIB_H

#include <avr/io.h>
#include <stdint.h>

uint8_t adc_read(uint8_t channel);
void adc_init(void);

#endif 