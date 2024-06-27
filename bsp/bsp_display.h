#ifndef __BSP_DISPLAY_H
#define __BSP_DISPLAY_H
#include "main.h"

#define DIGIT_0       0x01
#define DIGIT_1       0x02
#define DIGIT_2       0x04
#define DIGIT_3       0x08
#define DIGIT_4       0x10
#define DIGIT_5       0x20
#define DIGIT_6       0x40
#define DIGIT_7       0x80


void display_blink(uint8_t digits);
void display_clear(void);
void display_left_loop(void);
void display_right_loop(void);
void display_digit(uint8_t digit,uint8_t dat,uint8_t display_point);

#endif // __BSP_DISPLAY_H
