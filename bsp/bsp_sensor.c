#include "bsp_sensor.h"

sbit IO_DS18B20 = P1 ^ 3;

static void Delay500us(void);
static void Delay1ms(void);
static void Delay60us(void);

static uint8_t ds18b20_reset(void)
{
    uint8_t cnt = 0;
    IO_DS18B20  = 0;
    Delay500us();
    IO_DS18B20 = 1;
    while (IO_DS18B20) {
        cnt++;
        if (cnt > 5) {
            return 0;
        }
        Delay1ms();
    }
    return 1; // 初始化成功
}

static void ds18b20_write_byte(uint8_t dat)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        IO_DS18B20 = 0;
        _nop_();
        IO_DS18B20 = dat & 0x01;
        Delay60us();
        IO_DS18B20 = 1;
        dat >>= 1;
    }
}

void ds18b20_init(void)
{
    ds18b20_reset();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0x4E);
    ds18b20_write_byte(0x20);
    ds18b20_write_byte(0x00);
    ds18b20_write_byte(0x7F);
    ds18b20_reset();
}

static uint8_t ds18b20_read_byte(void)
{
    uint8_t i, dat = 0;
    for (i = 8; i > 0; i--) {
        IO_DS18B20 = 0;
        _nop_();
        dat >>= 1;
        IO_DS18B20 = 1;
        _nop_();
        _nop_();
        _nop_();
        if (IO_DS18B20) {
            dat |= (0x80);
        }
        Delay60us();
    }
    return dat;
}

static void ds18b20_convert_temperature_cmd(void)
{
    ds18b20_reset();
    Delay1ms();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0x44);
}

static void ds18b20_read_temperature_cmd(void)
{
    ds18b20_reset();
    Delay1ms();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0xBE);
}

void ds18b20_read_temperature(uint16_t *dat)
{
    uint16_t temp = 0;
    uint8_t MSB = 0, LSB = 0;
    ds18b20_convert_temperature_cmd();
    ds18b20_read_temperature_cmd();
    LSB = ds18b20_read_byte();
    MSB = ds18b20_read_byte();
    if (MSB & 0xf0) {
        // 温度为负数，错误
        *dat = 0;
    }
    *dat = (uint16_t)(MSB & 0x0f) << 8 | (LSB);
}

static void Delay60us(void) //@11.0592MHz
{
    unsigned char i;

    i = 25;
    while (--i);
}

static void Delay1ms(void) //@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}

static void Delay500us(void) //@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 227;
    while (--i);
}