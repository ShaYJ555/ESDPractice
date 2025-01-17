#ifndef __MAIN_H__
#define __MAIN_H__

#include "REG52.H"
#include "INTRINS.H"

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

#define EXT0_VECTOR  0 /* 0x03 external interrupt 0 */
#define TIM0_VECTOR  1 /* 0x0b timer 0 */
#define EXT1_VECTOR  2 /* 0x13 external interrupt 1 */
#define TIM1_VECTOR  3 /* 0x1b timer 1 */
#define UART0_VECTOR 4 /* 0x23 serial port 0 */

sbit LED   = P2 ^ 1;
sbit MOTOR = P1 ^ 2;

#endif // __MAIN_H
