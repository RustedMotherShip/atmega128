#include "main.h"

ISR(INT2_vect) {
    cli();
    // Обработка прерывания INT2
    menu_ok();
    //sei();
}

void setup(void)
{
    uart_init(9600);
    DDRA=0xFF;
    PORTA=0x00;
    PORTD=0x00;
    i2c_init();
    ssd1306_init();
    ssd1306_send_buffer();
    params_default_conf();
    adc_init();
    joystick_init(); 
}

int main(void)
{
    setup();

    while(1)
    {
        menu_set_paragraph(menu);
        menu_handler();
        addr_led_write_parameters();
    }
}

/*
 __  __________   ____  
|  \/   _   _  | |  _ \ 
| |\/| | | | | |_| |_) |
| |  | | | | |  _   _ < 
|_|  |_| |_| |_| |_| \_\
                    Inc. 
*/


