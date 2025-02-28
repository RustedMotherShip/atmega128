#include "adc_lib.h"

void adc_init(void) {

    DDRF = 0x00;
    // Включаем АЦП
    ADCSRA |= (1 << ADEN);
    
    // Устанавливаем предделитель (64 для 8 МГц, чтобы получить 125 кГц)
    ADCSRA  |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);; // 64 = 2^6, ADPS2 и ADPS1 = 1, ADPS0 = 0
    
    // Устанавливаем референсное напряжение (например, AVcc)
    ADMUX |= (1 << REFS0);
}

uint8_t adc_read(uint8_t channel) {
    // Выбираем канал (0-7)
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    
    // Запускаем преобразование
    ADCSRA |= (1 << ADSC);
    
    // Ждем завершения преобразования
    while (ADCSRA & (1 << ADSC));
    
    // Возвращаем результат
    return ADCW >> 2;
}
