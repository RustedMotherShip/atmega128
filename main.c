#include "main.h"

ISR(INT2_vect) {
    cli();
    // Обработка прерывания INT2
    menu_ok();
    sei();
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
void menu_handler()
{
        switch(check_axis_y())
        {
            case up:
                menu_up();
            break;
            case down:
                menu_down();
            break;
            default:
            break;
        };
        while(check_axis_y() != zero);
        menu_switch_paragraph();
}

int main(void)
{
    setup();
    menu_set_paragraph(menu);

    menu_set_params_value(255);
    _delay_ms(1000);
    menu_set_params_value(67);
    _delay_ms(1000);
    menu_set_params_value(9);
    _delay_ms(1000);
    while(1)
    {

        menu_handler();
        
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


