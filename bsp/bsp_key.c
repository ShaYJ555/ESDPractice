#include "bsp_key.h"
#include "hd7279a.h"

uint8_t key_scan(void)
{
    return hd7279a_read_data(CMD_READ);
}
