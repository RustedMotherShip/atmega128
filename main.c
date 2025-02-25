#include "main.h"

ISR(INT0_vect) {
    // Обработка прерывания INT2
    irq_joystick_flag = 1;
    PORTA =0xFF;
    //cli();

}
ISR(INT1_vect) {
    // Обработка прерывания INT2
    irq_joystick_flag = 1;
    PORTA =0xFF;
    //cli();

}
ISR(INT2_vect) {
    // Обработка прерывания INT2
    irq_joystick_flag = 1;
    PORTA =0xFF;
    //cli();

}

void setup(void)
{
    // uart_init(9600);
    DDRA=0xFF;
    PORTA=0x00;
    PORTD=0x00;
    // i2c_init();
    // ssd1306_init();
    // ssd1306_send_buffer();
    // params_default_conf();
    adc_init();
    joystick_init(); 
}
 
int main(void)
{
    setup();
    //menu_set_paragraph(menu);
    while(1)
    {
        // switch(check_axis_y())
        // {
        //     case up:
        //         menu_up();
        //     break;
        //     case down:
        //         menu_down();
        //     break;
        //     default:
        //     break;
        // };
        // while(check_axis_y() != zero);
        // menu_switch_paragraph();
        // if(irq_joystick_flag)
        // {
        //     menu_ok();
        //     irq_joystick_flag = 0;
        // }
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


