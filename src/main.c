#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_eeprom.h"
#include "bsp_display.h"
#include "bsp_console.h"
#include "hd7279a.h"

#include "main.h"
#include "menu.h"
#include "interrupt.h"
#include "algorithm.h"

#include <stdio.h>

void main()
{
    uint8_t dat[4] = {0};
    float temperature = 0;
    hd7279a_init();

    eeprom_write_bytes(0x00,dat,4);
    eeprom_read_bytes(0x00,dat,4);
    
    ds18b20_read_temperature(&temperature);
    
    console_init();
    while (1)
    {
        // TODO
    }
}

