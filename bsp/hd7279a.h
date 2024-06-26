#ifndef __HD7279A_H
#define __HD7279A_H
#include "main.h"

//****** HD7279A DE ******
#define CMD_RESET     0xa4
#define CMD_TEST      0xbf
#define DECODE0       0x80
#define DECODE1       0xc8
#define CMD_READ      0x15
#define UNDECODE      0x90
#define RTL_CYCLE     0xa3
#define RTR_CYCLE     0xa2
#define RTL_UNCYL     0xa1
#define RTR_UNCYL     0xa0
#define ACTCTL        0x98
#define SEGON         0xe0
#define SEGOFF        0xc0
#define BLINKCTL      0x88

void hd7279a_init(void);
void hd7279a_write_cmd(uint8_t cmd,uint8_t dat);
uint8_t hd7279a_read_data(uint8_t cmd);
void hd7279a_write_byte(uint8_t dat);

#endif // __HD7279A_H
