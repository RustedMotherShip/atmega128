#include "i2c_lib.h"

#include <util/twi.h>

#define I2C_FREQ 100000L // TWI frequency in Hz (100 kHz)

void i2c_init() {
    TWSR=0x00; //set presca1er bits to zero
    TWBR=0x46; //SCL frequency is 50K for 16Mhz
    TWCR=0x04; //enab1e TWI module
    // // Set TWI (Two-Wire Interface) bit rate
    // TWBR = ((F_CPU / I2C_FREQ) - 16) / 2;

    // // Enable TWI and set TWINT to 1 for no ongoing operation
    // TWCR = (1 << TWEN) | (1 << TWINT);

    // DDRD |= (1 << 0) | (1 << 1); // Set SDA and SCL as outputs
    // PORTD |= (1 << 0) | (1 << 1); // Enable pull-ups for SDA and SCL
}

void i2c_start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t i2c_send_address(uint8_t address, uint8_t rw_type)
{
    i2c_start();
    switch (rw_type)
    {
        case 1:
            address = (address << 1) | 0x01;
            break;
        default:
            address = address << 1;
            break;
    }

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    {
        return 0;
    }
    return 1;
}

uint8_t i2c_read_byte(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

void i2c_read(uint8_t dev_addr, uint8_t size, uint8_t *data)
{
    if (i2c_send_address(dev_addr, 1)) {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        for (int i = 0; i < size - 1; i++) {
            data[i] = i2c_read_byte();
        }
        TWCR = (1 << TWINT) | (1 << TWEN);
        data[size - 1] = i2c_read_byte();
        i2c_stop();
    }
}

uint8_t i2c_send_byte(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return (TWSR & 0xF8) == TW_MT_DATA_ACK;
}

void i2c_write(uint8_t dev_addr, uint8_t size, uint8_t *data)
{
    if (i2c_send_address(dev_addr, 0)) {
        for (int i = 0; i < size; i++) {
            if (!i2c_send_byte(data[i])) {
                break;
            }
        }
        i2c_stop();
    }
}

// void i2c_send_addr(uint8_t addr) {
//     TWDR = addr << 1;
//     TWCR = (1 << TWINT) | (1 << TWEN);
//     while (!(TWCR & (1 << TWINT)));
// }

// uint8_t i2c_send_byte(uint8_t data) {
//     TWDR = data;
//     TWCR = (1 << TWINT) | (1 << TWEN);
//     while (!(TWCR & (1 << TWINT)));
// }

// uint8_t i2c_read_byte(void) {
//     TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
//     while (!(TWCR & (1 << TWINT)));
//     return TWDR;
// }

// void i2c_write(uint8_t *data, uint8_t addr, uint8_t size)
// {
//     i2c_start();
//     i2c_send_addr(addr); // replace with the actual address of the slave device
//     for(int i = 0;i < size;i++)
//         i2c_send_byte(data[i]);
//     i2c_stop();
// }

// void i2c_write(uint8_t dev_addr,uint8_t size,uint8_t *data)
// {
//     if(i2c_send_address(dev_addr, 0))//Проверка на АСК бит
//     for(int i = 0;i < size;i++)
//         {
//             if(i2c_send_byte(data[i]))//Проверка на АСК бит
//             {
//                 break;//ошибка отправки нет ACK бита -> выход из цикла
//             } 
//         }
//     i2c_stop();
// }
// void i2c_read(uint8_t *data, uint8_t addr, uint8_t size) 
// {
//     i2c_start();
//     i2c_send_addr(addr | 0x01); // use the read address for the slave device
//     for(int i = 0;i < size;i++)
//         data[i] = i2c_read_byte();
//     i2c_stop();
// }

// uint8_t i2c_scan(void) 
// {
//     for (uint8_t addr = 1; addr < 127; addr++)
//     {
//         if(i2c_send_address(addr, 0))//отправка адреса на проверку 
//         {
//             i2c_stop();//адрес совпал 
//             return addr;// выход из цикла
//         }
//         I2C_SR2 -> AF = 0;//очистка флага ошибки
//     }
//     i2c_stop();//совпадений нет выход из функции
//     return 0;
// }