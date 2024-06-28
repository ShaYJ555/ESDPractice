#include "bsp_console.h"
#include <stdio.h>
sfr AUXR =0x8E;


void console_init(void)		//2400bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}


//发送一个字节数据
void sendByte(unsigned char dat){
   SBUF = dat;     //写入发送缓冲寄存器
   while(!TI);    //等待发送完成，TI发送溢出标志位 置1
   TI = 0;      //对溢出标志位清零	
}

/*
**重写printf调用的putchar函数，重定向到串口输出
**需要引入头文件<stdio.h>
*****/
char putchar(char c){
	//输出重定向到串口
	sendByte(c);
	return c;  //返回给函数的调用者printf
}



