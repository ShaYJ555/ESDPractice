#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "main.h"

#define KEY_UP       58
#define KEY_DOWN     59
#define KEY_BACK     57
#define KEY_ENTER    56

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
