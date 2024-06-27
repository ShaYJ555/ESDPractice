#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "main.h"

#define KEY_UP       0x59
#define KEY_DOWN     0x60
#define KEY_BACK     0x63
#define KEY_ENTER    0x56

typedef struct
{
    uint8_t key_status;
    uint8_t key_judge;
    uint8_t key_timer;
    uint8_t key_short;
    uint8_t key_long;
}Key_t;



uint8_t key_scan(void);

#endif // __BSP_KEY_H
