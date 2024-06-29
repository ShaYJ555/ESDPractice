#include "bsp_eeprom.h"

// 51单片机定义I2C总线用于通信
sbit I2C_SDA = P1 ^ 0;
sbit I2C_SCL = P1 ^ 1;

static void Delay10us(void);
static void Delay10ms(void);

// 编写一个IIC写函数
static void IIC_start(void)
{
    I2C_SDA = 1;
    Delay10us();
    I2C_SCL = 1;
    Delay10us();
    I2C_SDA = 0;
    Delay10us();
    I2C_SCL = 0;
    Delay10us();
}

static void IIC_stop(void)
{
    I2C_SDA = 0;
    Delay10us();
    I2C_SCL = 1;
    Delay10us();
    I2C_SDA = 1;
    Delay10us();
}

static void IIC_ack(void)
{
    I2C_SCL = 0;
    I2C_SDA = 0;
    Delay10us();
    I2C_SCL = 1;
    Delay10us();
    I2C_SCL = 0;
}

static void IIC_nack(void)
{
    I2C_SCL = 0;
    I2C_SDA = 1;
    Delay10us();
    I2C_SCL = 1;
    Delay10us();
    I2C_SCL = 0;
}

static uint8_t IIC_wait_ack(void)
{
    uint8_t temp = 0;
    I2C_SCL      = 1;
    Delay10us();
    while (I2C_SDA) {
        temp++;
        if (temp > 100) {
            IIC_stop();
            return 1;
        }
    }
    I2C_SCL = 0;
    return 0;
}

static void IIC_write_byte(uint8_t dat)
{
    uint8_t i = 0;
    I2C_SCL   = 0;
    for (i = 0; i < 8; i++) {
        if (dat & 0x80) {
            I2C_SDA = 1;
        } else {
            I2C_SDA = 0;
        }
        Delay10us();
        I2C_SCL = 1;
        Delay10us();
        I2C_SCL = 0;
        Delay10us();
        dat <<= 1;
    }
}

static uint8_t IIC_read_byte(uint8_t ack)
{
    uint8_t i = 0, dat = 0;
    for (i = 0; i < 8; i++) {
        I2C_SCL = 0;
        Delay10us();
        I2C_SCL = 1;
        dat <<= 1;
        if (I2C_SDA) {
            dat++;
        }
        Delay10us();
    }
    if (ack) {
        IIC_ack();
    } else {
        IIC_nack();
    }
    return dat;
}

static void eeprom_write_byte(uint8_t addr, uint8_t dat)
{
    IIC_start();
    IIC_write_byte(EEPROM_ADDR | ((addr / 256) << 1)); // 发送写命令
    IIC_wait_ack();
    IIC_write_byte(addr % 256);
    IIC_wait_ack();
    IIC_write_byte(dat);
    IIC_wait_ack();
    IIC_stop();
    Delay10ms();
}
static uint8_t eeprom_read_byte(uint8_t addr)
{
    uint8_t dat = 0;
    IIC_start();
    IIC_write_byte(EEPROM_ADDR | ((addr / 256) << 1));
    IIC_wait_ack();
    IIC_write_byte(addr % 256);
    IIC_wait_ack();
    IIC_start();
    IIC_write_byte(EEPROM_ADDR | ((addr / 256) << 1) | 0x01);
    IIC_wait_ack();
    dat = IIC_read_byte(0);
    IIC_stop();
    return dat;
}

void eeprom_write_bytes(uint8_t addr, uint8_t *dat, uint8_t len)
{
    while (len--) {
        eeprom_write_byte(addr++, *dat++);
    }
}

void eeprom_read_bytes(uint8_t addr, uint8_t *dat, uint8_t len)
{
    while (len--) {
        *dat++ = eeprom_read_byte(addr++);
    }
}

static void Delay10us() //@11.0592MHz
{
    unsigned char i;

    i = 2;
    while (--i);
}

static void Delay10ms() //@11.0592MHz
{
    unsigned char i, j;

    i = 18;
    j = 235;
    do {
        while (--j);
    } while (--i);
}