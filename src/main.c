#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_eeprom.h"
#include "bsp_display.h"
#include "hd7279a.h"

#include "main.h"
#include "menu.h"
#include "interrupt.h"
#include "algorithm.h"

void Delay120ms(void);

uint16_t temperature;
uint8_t last_menu_index = 0;
uint8_t now_menu_index = 0; 
uint8_t key_value = 0;
uint8_t select_index = 1;

uint8_t motor_test[11] = {0,70,71,72,73,74,75,76,77,78,79}; 

void main()
{
    Timer0_Init();
    hd7279a_init();
    ds18b20_init();
    menu_init();
    ds18b20_read_temperature(&temperature);
    while (1)
    {
        EA = 0;
        key_value = key_scan();
        EA = 1;
        switch (key_value)
        {
        case KEY_UP:
            if(menu_list[last_menu_index].up != NULL_MENU_ID)
            {
                now_menu_index = menu_list[last_menu_index].up;
            }
            break;
        case KEY_DOWN:
            if (menu_list[last_menu_index].down != NULL_MENU_ID)
            {
                now_menu_index = menu_list[last_menu_index].down;
            }    
            break;
        case KEY_BACK:
            if (menu_list[last_menu_index].back != NULL_MENU_ID)
            {
                now_menu_index = menu_list[last_menu_index].back;
            }   
            break;
        case KEY_ENTER:
            if (menu_list[last_menu_index].enter != NULL_MENU_ID)
            {
                now_menu_index = menu_list[last_menu_index].enter;
            }
            break;        
        }
        if(now_menu_index != last_menu_index)
        {
            display_clear();
            menu_list[now_menu_index].current_menu();
            last_menu_index = now_menu_index;
        }
        Delay120ms();
        if(now_menu_index == TEMP_PARAM_MENU_ID)
		{
			EA = 0;
			ds18b20_read_temperature(&temperature);
            display_clear();
			TEMP_PARAM_MENU();
			EA = 1;
		}
        if(now_menu_index == MOTOR_SELECT_MENU_ID)
        {
            switch (key_value)
            {
            case KEY_UP:
                select_index++;
                if (select_index > 10)
                {
                    select_index = 1;
                }
                EA = 0;
                display_clear();
                MOTOR_SELECT_MENU();
                EA = 1;
                break;
            case KEY_DOWN:
                select_index--;
                if(select_index < 1)
                {
                    select_index = 10;
                }
                EA = 0;
                display_clear();
                MOTOR_SELECT_MENU();
                EA = 1;
                break;
            }
        }
    }
}

void Delay120ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 216;
	j = 37;
	do
	{
		while (--j);
	} while (--i);
}