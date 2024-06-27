#include "interrupt.h"
#include "bsp_key.h"

sfr AUXR =0x8E;

// 自动重装载
void Timer0_Init(void)		//10毫秒@11.0592MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xDC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void Timer0_Proc(void) interrupt TIM0_VECTOR
{
	key_handler();

}
