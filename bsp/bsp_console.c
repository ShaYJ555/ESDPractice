#include "bsp_console.h"

sfr AUXR =0x8E;

void console_init(void)		//2400bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0x80;			//���ö�ʱ��ʼֵ
	TH1 = 0xFB;			//���ö�ʱ��ʼֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ

    TI = 1;             //ֱ��ʹ��printf�������˾����ʵ�ַ���
}