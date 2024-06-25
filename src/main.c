/**
 * *********************************************
 * 
 * 8051 blink demo
 * 
 * PIN: P11
 * 
 * *********************************************
*/
#include "REG52.H"

#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_eeprom.h"
#include "bsp_display.h"

#include "main.h"
#include "interrupt.h"
#include "algorithm.h"


void main()
{

    while (1)
    {
        // TODO
    }
}

void TIM0_Handler() interrupt TIM0_VECTOR
{
    static uint16_t count;

    TH0 = 0xFC;
    TL0 = 0x18;

    // 500 ms
    if (++count >= 500)
    {
        count = 0;
        LED = !LED;
    }
}
