#include "main.h"

void setup(void)
{
    
    
    DDRA = 0xFF;
    PORTA = 0x00;
    uart_init(9600);
    i2c_init();
    ssd1306_init();
    ssd1306_send_buffer();
    params_default_conf();
    adc_init();
}
 
int main(void)
{
    setup();
    menu_set_paragraph(menu);
    while(1)
    {
        switch(check_axis())
        {
            case up:
                menu_up();
            break;
            case down:
                menu_down();
            break;
            case left:
                menu_left();
            break;
            case right:
                menu_right();
            break;
            case button:
                menu_ok_button();
            break;
            default:
            break;
        }
    };
}

/*
 __  __________   ____  
|  \/   _   _  | |  _ \ 
| |\/| | | | | |_| |_) |
| |  | | | | |  _   _ < 
|_|  |_| |_| |_| |_| \_\
                    Inc. 
*/


