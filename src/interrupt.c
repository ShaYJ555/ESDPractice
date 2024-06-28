#include "interrupt.h"
#include "bsp_key.h"
#include "bsp_sensor.h"
#include "menu.h"

sfr AUXR =0x8E;

// �Զ���װ��
void Timer0_Init(void)		//10����@11.0592MHz
{
	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0xDC;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ

	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

void Timer0_Handler(void) interrupt TIM0_VECTOR
{
	static uint8_t cnt = 0;
	cnt++;
	if(cnt==5)
	{

	}
	
}
