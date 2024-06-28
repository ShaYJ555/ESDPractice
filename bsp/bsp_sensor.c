#include "bsp_sensor.h"

sbit IO_DS18B20 = P1^3;

void Delay500us();
void Delay1ms();
void Delay60us();



uint8_t ds18b20_reset()
{
    uint8_t cnt = 0;
    IO_DS18B20 = 0;
    Delay500us();
    IO_DS18B20 = 1;
    while (IO_DS18B20)
    {
        cnt++;
        if(cnt>5)
        {
            return 0;
        }
        Delay1ms();
    }
    return 1;    // 初始化成功
}



void ds18b20_write_byte(uint8_t dat)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        IO_DS18B20 = 0;
        _nop_();
        IO_DS18B20 = dat & 0x01;
        Delay60us();
        IO_DS18B20 = 1;
        dat >>= 1;
    }
}

void ds18b20_init()
{
    ds18b20_reset();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0x4E);
    ds18b20_write_byte(0x20);
    ds18b20_write_byte(0x00);
    ds18b20_write_byte(0x7F);   
    ds18b20_reset();
}

uint8_t ds18b20_read_byte()
{
    uint8_t i,dat=0;
    for (i = 8; i > 0; i--)
    {
        IO_DS18B20 = 0;
        _nop_();
        dat >>= 1;
        IO_DS18B20 = 1;
        _nop_();
        _nop_();
        _nop_();
        if(IO_DS18B20)
        {
            dat |= (0x80);
        }
        Delay60us();
    }
    return dat;
}

void ds18b20_convert_temperature_cmd(void)
{
    ds18b20_reset();
    Delay1ms();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0x44);
}

void ds18b20_read_temperature_cmd(void)
{
    ds18b20_reset();
    Delay1ms();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0xBE);    
}

void ds18b20_read_temperature(int16_t *dat)
{
    int16_t temp = 0;
    uint8_t MSB = 0,LSB = 0;
    ds18b20_convert_temperature_cmd();
    ds18b20_read_temperature_cmd();
    LSB = ds18b20_read_byte();
    MSB = ds18b20_read_byte();
    if(MSB&0xf0)
    {
        // 温度为负数，错误
        *dat = 0;
    }
    *dat = (int16_t)(MSB&0x0f)<<8 | (LSB);
}


void Delay60us()		//@11.0592MHz
{
	unsigned char i;

	i = 25;
	while (--i);
}
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}