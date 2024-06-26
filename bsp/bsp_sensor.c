#include "bsp_sensor.h"
#include "main.h"

sbit IO_18B20 = P1^3;

static void Delay500us(void);
static void Delay60us(void);
static void Delay2us(void);
static uint8_t ds18b20_get_ack()
{
    uint8_t ack = 0;

    EA = 0;                 // ��ֹ���ж�

    IO_18B20 = 0;           // ������λ����
    Delay500us();
    IO_18B20 = 1;
    Delay60us();
    ack = IO_18B20;
    while (!IO_18B20);      // �ȴ���������

    EA = 1;                 // �������ж�
    
    return ack;
}

static void ds18b20_write_byte(uint8_t dat)
{
    uint8_t mask = 0;

    EA = 0;                 // ��ֹ���ж�

    for (mask = 0x01; mask != 0; mask << 1)
    {
        IO_18B20 = 0;       // ���� 2us �͵�ƽ����
        Delay2us();
        if(mask&dat)
        {
            IO_18B20 = 1;
        }
        else
        {
            IO_18B20 = 0;
        }
        Delay60us();
        IO_18B20 = 1;
    }
    
    EA = 1;                 // �������ж�
}

static uint8_t ds18b20_read_byte(void)
{
    uint8_t dat = 0;
    uint8_t mask = 0;

    EA = 0;                 // ��ֹ���ж�
    for (mask = 0x01; mask != 0; mask << 1)
    {
        IO_18B20 = 0;       // ���� 2us �͵�ƽ����
        Delay2us();
        IO_18B20 = 1;
        Delay2us();
        if(IO_18B20)        // ��ȡ����
        {
            dat |= mask;
        }
        else
        {
            dat &= ~mask;
        }
    }

    EA = 1;                 // �������ж�
    
    return dat;        
}

static uint8_t ds18b20_start(void)
{
    uint8_t ack = 0;
    ack = ds18b20_get_ack();       // ��ȡ����״̬
    if(ack == 0)
    {
        ds18b20_write_byte(0xCC);   // ����ROM
        ds18b20_write_byte(0x44);   // �����¶�ת��
    }
    return ~ack;                    // 1��ʾ������0��ʾ�쳣
}

void ds18b20_read_temperature(float *temperature)
{
    uint8_t ack = 0;
    int16_t temp = 0;
    uint8_t LSB = 0,MSB = 0;       // �洢�¶�����

    if(!ds18b20_start())
    {
        *temperature = 0.0;
        return;
    }
    
    ack = ds18b20_get_ack();       // ��ȡ����״̬
    if(ack == 0)
    {
        ds18b20_write_byte(0xCC);   // ����ROM
        ds18b20_write_byte(0xBE);   // ��ȡ����
        LSB = ds18b20_read_byte();
        MSB = ds18b20_read_byte();
        temp = ((int16_t)MSB<<8) | LSB;
        if(temp>0)
        {
            *temperature = (float)(temp & 0x0F)/16 + (float)((temp>>4)&0x7F);
        }
        else
        {
            *temperature = -((float)(temp & 0x0F)/16 + (float)((temp>>4)&0x7F));
        }
    }
}

static void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

static void Delay60us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 163;
	while (--i);
}

static void Delay2us()		//@11.0592MHz
{
	unsigned char i;

	i = 3;
	while (--i);
}




