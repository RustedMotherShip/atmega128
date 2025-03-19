#include "i2c_lib.h"

void i2c_init(void)
{

    TWSR=0x00; //set presca1er bits to zero
    // Set TWI (I2C) bit rate to 100 kbps
    TWBR = ((F_CPU / 100000) - 16) / 2;
    // Enable TWI (I2C) module
    TWCR |= (1 << TWEN);
}

void i2c_start()
{
    cli();
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
    while (!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t i2c_send_address(uint8_t address, uint8_t rw_type)
{
    switch (rw_type)
    {
        case 1:
            address = (address << 1) | 0x01;
            break;
        default:
            address = address << 1;
            break;
    }

    i2c_start();
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWIE);
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
