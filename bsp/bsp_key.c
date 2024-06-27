#include "bsp_key.h"
#include "hd7279a.h"
#include "main.h"

Key_t key[4] = {0};
uint8_t key_scan(void)
{
    return hd7279a_read_data(CMD_READ);
}

uint8_t key_handler(void)
{
    uint8_t i = 0;
    key[0].key_status  = key_scan()&KEY_UP;
    key[1].key_status  = key_scan()&KEY_DOWN;
    key[2].key_status  = key_scan()&KEY_BACK;
    key[3].key_status  = key_scan()&KEY_ENTER;
    for (i = 0; i < 4; i++)
    {
        if(key[i].key_status)
        {
            key[i].key_timer++;
            if(key[i].key_timer > 50)
            {
                key[i].key_timer = 0;
                key[i].key_long  = 1;
                key[i].key_judge = 0;
            }
            else
            {
                key[i].key_timer = 0;
                key[i].key_short = 1;
                key[i].key_judge = 0;                
            }
        }
    }
}
