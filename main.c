#include "main.h"

// void params_default_conf(void)
// {
//     params_value.current_red = 255;
//     params_value.current_green = 255;
//     params_value.current_blue = 255;

//     params_value.current_first = 0;
//     params_value.current_second = 15;

//     params_value.current_sens = 10;
//     params_value.current_vers = 0xA1;
// }

void setup(void)
{
    //params_value.all = 0;
    
    
    uart_init(9600);
    i2c_init();
    ssd1306_init();
    ssd1306_send_buffer();
    //params_default_conf();
    //enableInterrupts();
    //adc_init();
}



 
int main(void)
{
    _delay_ms(2000);
    setup();

    while(1)
    {
        //uart_write_byte(adc_read());
        //delay_s(1);
        //menu_set_paragraph(menu);
        //menu_set_paragraph(color);
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


