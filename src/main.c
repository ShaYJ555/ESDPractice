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

uint8_t last_menu_index = 0;
uint8_t now_menu_index = 0; 

void main()
{
    uint8_t dat[4] = {0};
    uint8_t key_value = 0;
    int16_t temperature = 0;

    hd7279a_init();

    eeprom_write_bytes(0x00,dat,4);
    eeprom_read_bytes(0x00,dat,4);
    
    ds18b20_read_temperature(&temperature);
    
    console_init();
    while (1)
    {
        switch (key_scan())
        {
        case KEY_UP:
            if(menu_list[now_menu_index].up != NULL_MENU_ID)
            {
                now_menu_index = menu_list[now_menu_index].up;
            }
            break;
        case KEY_DOWN:
            if (menu_list[now_menu_index].down != NULL_MENU_ID)
            {
                now_menu_index = menu_list[now_menu_index].down;
            }    
            break;
        case KEY_BACK:
            if (menu_list[now_menu_index].back != NULL_MENU_ID)
            {
                now_menu_index = menu_list[now_menu_index].back;
            }   
            break;
        case KEY_ENTER:
            if (menu_list[now_menu_index].enter != NULL_MENU_ID)
            {
                now_menu_index = menu_list[now_menu_index].enter;
            }
            break;        
        }
        if(now_menu_index != last_menu_index)
        {
            display_clear();
            menu_list[last_menu_index].current_menu();
            last_menu_index = now_menu_index;
        }
    }
}

