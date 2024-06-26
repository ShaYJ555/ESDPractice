#include "bsp_display.h"
#include "hd7279a.h"

// 编写一个数组，用于索引0-9数字
uint8_t digit_array[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void display_digit(uint8_t digit,uint8_t dat,uint8_t display_point)
{
    if(display_point == 1)
    {
        dat = dat | 0x80;
    }
    switch(digit)
    {
        case DIGIT_0:
            hd7279a_write_cmd(UNDECODE|0,dat);
            break;
        case DIGIT_1:
            hd7279a_write_cmd(UNDECODE|1,dat);
            break;
        case DIGIT_2:
            hd7279a_write_cmd(UNDECODE|2,dat);
            break;
        case DIGIT_3:
            hd7279a_write_cmd(UNDECODE|3,dat);
            break;
        case DIGIT_4:
            hd7279a_write_cmd(UNDECODE|4,dat);
            break;
        case DIGIT_5:
            hd7279a_write_cmd(UNDECODE|5,dat);
            break;
        case DIGIT_6:
            hd7279a_write_cmd(UNDECODE|6,dat);
            break;
        case DIGIT_7:
            hd7279a_write_cmd(UNDECODE|7,dat);
            break;           
    }
}

void display_blink(uint8_t digits)
{
    hd7279a_write_cmd(BLINKCTL,digits);
}

void display_left_loop(void)
{
    hd7279a_write_byte(RTL_CYCLE);
}

void display_right_loop(void)
{
    hd7279a_write_byte(RTR_CYCLE);
}