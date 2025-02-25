#include "ssd1306_lib.h"

static uint8_t main_buffer[512] =
{
0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x01,  
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,  
0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,  
0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  
0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,  
0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  
0x01, 0x01, 0x01, 0x3D, 0x15, 0x3D, 0x01, 0x3D, 0x21, 0x21, 0x01, 0x3D, 0x15, 0x1D, 0x01, 0x3D,  
0x11, 0x3D, 0x01, 0x3D, 0x15, 0x3D, 0x01, 0x01, 0x3D, 0x25, 0x3D, 0x01, 0x05, 0x3D, 0x01, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,  
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x01,  
0x01, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01,  
0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFF,  
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,  
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,  
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,  
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x80, 0x80,  
0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,  
0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 0x80, 0x80,  
0x80, 0x80, 0x80, 0x80, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x80, 0x80, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  
0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xBF, 0xBF, 
0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 0x80, 0x80, 0xB1, 0xB1, 0xBF, 0xBF, 0xBF, 0xB1, 0xB1, 0x80, 
0x80, 0xBF, 0xBF, 0x83, 0x83, 0xBF, 0xBE, 0x80, 0x80, 0xBF, 0xBF, 0xB3, 0xB3, 0xB3, 0xB3, 0x80, 
0x80, 0x80, 0x80, 0xB0, 0xB0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF,
};

int get_bit(int data,int bit)
{
    return ((data >> bit) & 1) ? 1 : 0;
}
int set_bit(int data,int bit, int value)
{
    int mask = 1 << bit ;
    switch(value)
    {
        case 1:
            data |= mask;
        break;

        default:
            data &= ~mask;
        break;
    }
    return data;
}

void ssd1306_init(void)
{
    uint8_t setup_buffer[27] = {COMMAND, 
                                SET_DISPLAY_OFF, 
                                SET_DISPLAY_CLOCK_DIV, 0x80,
                                SET_MULTIPLEX, 0x1F,
                                SET_DISPLAY_OFFSET, 0x00,
                                SET_DISPLAY_START_LINE,
                                SET_CHARGE_PUMP, 0x14,
                                SET_VCOM_DETECT, 0x40,
                                SET_DISPLAY_ALL_ON_RESUME,
                                SET_NORMAL_DISPLAY,
                                SET_COM_PINS, 0x02,
                                SET_CONTRAST, 0x8F,
                                SET_PRECHARGE_PERIOD, 0xF1,
                                SET_MEMORY_MODE, 0x00,
                                SET_SEG_REMAP,
                                SET_COM_SCAN_DIR, 0x1F,
                                SET_DISPLAY_ON};
    i2c_write(I2C_DISPLAY_ADDR, 27, setup_buffer);

}

void ssd1306_set_params_to_write(void)
{
    uint8_t set_params_buf[7] = {COMMAND,
                                 SET_PAGE_ADDRESS,0x00,0x03,
                                 SET_COLUMN_ADDRESS,0x00,0x7F};

    i2c_write(I2C_DISPLAY_ADDR,7,set_params_buf);
}

void ssd1306_draw_pixel(uint8_t *buffer, uint8_t x, uint8_t y, uint8_t color)
{
    buffer[x + ((y / 8) * SSD1306_LCDWIDTH)] = set_bit(buffer[x + ((y / 8) * SSD1306_LCDWIDTH)],(y % 8),color);
}

void ssd1306_buffer_clean(void)
{
    memset(main_buffer,0,512);
}
void ssd1306_send_buffer(void)
{
    ssd1306_set_params_to_write();
    for(uint16_t j = 0;j<4;j++)
    {
        if(i2c_send_address(I2C_DISPLAY_ADDR, 0))//Проверка на АСК бит
        {
            i2c_send_byte(SET_DISPLAY_START_LINE);
            for(uint16_t i = 0;i < 128;i++)
            {
                if(!i2c_send_byte(main_buffer[i+(128*j)]))//Проверка на АСК бит
                {
                    break;//ошибка отправки нет ACK бита -> выход из цикла
                } 
            }
            i2c_stop();
        }
        else
        i2c_stop();
    }
}

void ssd1306_buffer_write(int x, int y, const uint8_t *data)
{
    for (int height = 0; height < 8; height++)
    {
        for (int width = 0; width < 8; width++)
            if(data[height + width / 8] & (128 >> (width & 7)))
            ssd1306_draw_pixel(main_buffer, x + width, y + height, get_bit(data[height], 7 - (width % 8)));
    }
}

void ssd1306_clean(void)
{
    ssd1306_buffer_clean();
    ssd1306_send_buffer();
}