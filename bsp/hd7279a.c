#include "hd7279a.h"

sbit HD7279A_CS   = P1^4; 
sbit HD7279A_CLK  = P1^5; 
sbit HD7279A_DATA = P1^7; 
sbit HD7279A_KEY  = P1^6; 

static void Delay10us(void);
static void Delay15us(void);		
static uint8_t hd7279a_read_byte(void);


void hd7279a_init(void)
{
	hd7279a_write_byte(CMD_RESET);
}

void hd7279a_write_cmd(uint8_t cmd,uint8_t dat)
{
    hd7279a_write_byte(cmd);
    hd7279a_write_byte(dat);
}

uint8_t hd7279a_read_data(uint8_t cmd)
{
    hd7279a_write_byte(cmd);
    return hd7279a_read_byte();
}

void hd7279a_write_byte(uint8_t dat)
{
    uint8_t i = 0;
    HD7279A_CS = 0;
    Delay15us();
    for (i = 0;i<8;i++)
    {
        if (dat&0x80)
        {
            HD7279A_DATA=1;
        }
        else
        {
            HD7279A_DATA=0;
        }
        HD7279A_CLK=1;
        Delay10us();
        HD7279A_CLK=0;
        Delay10us();
        dat = dat << 1;
    }
    HD7279A_DATA=0;
}

static uint8_t hd7279a_read_byte(void)
{
    uint8_t dat = 0, i = 0;
    HD7279A_DATA = 1; // ÉèÖÃÎªÊäÈë×´Ì¬
    Delay15us();
    for (i = 0;i < 8; i++)
    {
        HD7279A_CLK = 1;
        Delay10us();
        dat = dat << 1;
        if (HD7279A_DATA)
        {
            dat = dat|0x01;
        }
        HD7279A_CLK = 0;
        Delay10us();
    }
    HD7279A_DATA = 0;
    return dat;
}


static void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 4;
	while (--i);
}

static void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}
