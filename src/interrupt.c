#include "interrupt.h"
#include "bsp_key.h"
#include "bsp_sensor.h"
#include "menu.h"

sfr AUXR = 0x8E;

uint8_t duty = 0;

// 自动重装载
void Timer0_Init(void) // 34.75微秒@11.0592MHz
{
    AUXR |= 0x80; // 定时器时钟1T模式
    TMOD &= 0xF0;
    TMOD |= 0x02;
    TL0 = 0xF0;
    TH0 = 0xF0;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA  = 1;
}

void Timer0_Handler(void) interrupt TIM0_VECTOR
{
    static uint8_t pwm_cnt = 0;
    pwm_cnt++;
    if (pwm_cnt >= duty) {
        MOTOR = 0;
    } else {
        MOTOR = 1;
    }
    if (pwm_cnt > 100) {
        pwm_cnt = 0;
    }
}
