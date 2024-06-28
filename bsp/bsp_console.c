#include "bsp_console.h"
#include <stdio.h>
sfr AUXR =0x8E;


void console_init(void)		//2400bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}


//����һ���ֽ�����
void sendByte(unsigned char dat){
   SBUF = dat;     //д�뷢�ͻ���Ĵ���
   while(!TI);    //�ȴ�������ɣ�TI���������־λ ��1
   TI = 0;      //�������־λ����	
}

/*
**��дprintf���õ�putchar�������ض��򵽴������
**��Ҫ����ͷ�ļ�<stdio.h>
*****/
char putchar(char c){
	//����ض��򵽴���
	sendByte(c);
	return c;  //���ظ������ĵ�����printf
}



