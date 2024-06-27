#include "interrupt.h"
#include "bsp_key.h"

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
}

void Timer0_Proc(void) interrupt TIM0_VECTOR
{
	key_handler();

}
