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
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


uint8_t last_menu_index = 0;
uint8_t now_menu_index = 0; 

void main()
{
    uint8_t dat[4] = {0xAA,0xBB,0xCC,0xDD};
    uint8_t buffer[4] = {0};
    uint8_t d[3] = {0};
    uint8_t key_value = 0;
    int16_t temp = 0;
    uint16_t temp_param = 0;
    hd7279a_init();
    ds18b20_init();
    // eeprom_write_bytes(0x001ff,dat,4);
    // eeprom_read_bytes(0x001ff,buffer,4);

    // d[0] = buffer[0] / 100;
    // d[1] = buffer[0] / 10 % 10;
    // d[2] = buffer[0] % 10;

    // display_digit(DIGIT_5,digit_array[d[0]],0);
    // display_digit(DIGIT_6,digit_array[d[1]],0);          
    // display_digit(DIGIT_7,digit_array[d[2]],0);    
    while (1)
    {
        // Delay100ms();
        // EA = 0;
        // ds18b20_read_temperature(&temp);
        // EA = 1;
        // d[0] = temp / 100;
        // d[1] = temp / 10 % 10;
        // d[2] = temp % 10;
        // display_digit(DIGIT_5,digit_array[d[0]],0);
        // display_digit(DIGIT_6,digit_array[d[1]],0);          
        // display_digit(DIGIT_7,digit_array[d[2]],0);

        // temp_param = (uint16_t)((float)temp * 6.25);

        // dat[0] = temp_param / 1000;
        // dat[1] = temp_param % 1000  / 100;
        // dat[2] = temp_param % 100   / 10;
        // dat[3] = temp_param % 10;

        // display_digit(DIGIT_0,digit_array[dat[0]],0);
        // display_digit(DIGIT_1,digit_array[dat[1]],0);
        // display_digit(DIGIT_2,digit_array[dat[2]],0);
        // display_digit(DIGIT_3,digit_array[dat[3]],0);
        switch (key_scan())
        {
        case KEY_UP:
            display_digit(DIGIT_4,digit_array[1],0);
            // if(menu_list[now_menu_index].up != NULL_MENU_ID)
            // {
                
            //     now_menu_index = menu_list[now_menu_index].up;
            // }
            break;
        case KEY_DOWN:
            display_digit(DIGIT_4,digit_array[2],0);
            // if (menu_list[now_menu_index].down != NULL_MENU_ID)
            // {
                
            //     now_menu_index = menu_list[now_menu_index].down;
            // }    
            break;
        case KEY_BACK:
            display_digit(DIGIT_4,digit_array[3],0);
            // if (menu_list[now_menu_index].back != NULL_MENU_ID)
            // {
                
            //     now_menu_index = menu_list[now_menu_index].back;
            // }   
            break;
        case KEY_ENTER:
            display_digit(DIGIT_4,digit_array[4],0);
            // if (menu_list[now_menu_index].enter != NULL_MENU_ID)
            // {
                
            //     now_menu_index = menu_list[now_menu_index].enter;
            // }
            break;        
        }
        // if(now_menu_index != last_menu_index)
        // {
        //     display_clear();
        //     menu_list[last_menu_index].current_menu();
        //     last_menu_index = now_menu_index;
        // }
    }
}

