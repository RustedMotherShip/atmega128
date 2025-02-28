#ifndef SSD1306_LIB_H
#define SSD1306_LIB_H

#include <stdint.h>
#include "i2c_lib.h"
#include <string.h>

#define WHITE 1
#define BLACK 0
#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 32
#define I2C_DISPLAY_ADDR 0x3C

//Список всех команд

#define COMMAND 0x00 
#define SET_DISPLAY_OFF 0xAE                  // Выключить дисплей
#define SET_DISPLAY_ON 0xAF                   // Включить дисплей
#define SET_DISPLAY_CLOCK_DIV 0xD5        // Установить делитель тактовой частоты дисплея
#define SET_MULTIPLEX 0xA8                // Установить мультиплексное соотношение
#define SET_DISPLAY_OFFSET 0xD3            // Установить смещение дисплея
#define SET_CHARGE_PUMP 0x8D                  // Управление зарядным насосом
#define SET_MEMORY_MODE 0x20                  // Установить режим памяти
#define SET_SEG_REMAP 0xA0                    // Переключить отображение сегментов
#define SET_COM_SCAN_DIR 0xC0                 // Установить направление сканирования COM
#define SET_COM_PINS 0xDA                 // Установить пины COM
#define SET_CONTRAST 0x81                 // Установить контрастность
#define SET_PRECHARGE_PERIOD 0xD9             // Установить предзарядный период
#define SET_VCOM_DETECT 0xDB                  // Установить детектор VCOM
#define SET_DISPLAY_ALL_ON_RESUME 0xA4        // Возобновить отображение после полного включения
#define SET_PAGE_ADDRESS 0x22             // Установить адрес страницы
#define SET_COLUMN_ADDRESS 0x21           // Установить адрес столбца
#define SET_HIGH_COLUMN 0x10              // Установить высокий байт адреса столбца
#define SET_LOW_COLUMN 0x00               // Установить низкий байт адреса столбца
#define SET_DEACTIVATE_SCROLL 0x2E             // Деактивировать прокрутку
#define SET_ACTIVATE_SCROLL 0x2F               // Активировать прокрутку
#define SET_VERTICAL_SCROLL_AREA 0xA3      // Установить область вертикальной прокрутки
#define SET_RIGHT_HORIZONTAL_SCROLL 0x26       // Горизонтальная прокрутка вправо
#define SET_LEFT_HORIZONTAL_SCROLL 0x27        // Горизонтальная прокрутка влево
#define SET_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 // Вертикальная и горизонтальная прокрутка вправо
#define SET_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  // Вертикальная и горизонтальная прокрутка влево
#define SET_PRECHARGE_VOLTAGE 0xBB         // Установить напряжение предзарядки
#define SET_VCOMH_DESELECT_LEVEL 0xBE      // Установить уровень VCOMH
#define SET_DISPLAY_START_LINE 0x40        // Установить начальную линию дисплея
#define SET_INVERSE_DISPLAY 0xA7           // Установить инвертированный режим отображения
#define SET_NORMAL_DISPLAY 0xA6            // Установить нормальный режим отображения
     

//  ____  ____  _        _    ____  _   _ 
// / ___||  _ \| |      / \  / ___|| | | |
// \___ \| |_) | |     / _ \ \___ \| |_| |
//  ___) |  __/| |___ / ___ \ ___) |  _  |
// |____/|_|   |_____/_/   \_\____/|_| |_|

void ssd1306_init(void);
void ssd1306_set_params_to_write(void);
void ssd1306_draw_pixel(uint8_t *buffer,uint8_t x, uint8_t y, uint8_t color);
void ssd1306_buffer_splash(void);
void ssd1306_buffer_write(int x, int y, const uint8_t *data);
void ssd1306_buffer_write_void(int x, int y);
void ssd1306_clean(void);
void ssd1306_buffer_clean(void);
void ssd1306_send_buffer(void);
void ssd1306_display_clean(void);

#endif 