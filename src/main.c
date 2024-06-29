#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_eeprom.h"
#include "bsp_display.h"
#include "hd7279a.h"

#include "main.h"
#include "menu.h"
#include "interrupt.h"
#include "algorithm.h"

void Delay10ms(void);

uint16_t temperature;
uint8_t last_menu_index = 0;
uint8_t now_menu_index = 0; 
uint8_t key_value = 0;
uint8_t select_index = 1;
uint8_t pa_select_index = 1;
uint8_t motor_test[11] = {0,10,20,30,40,50,60,70,80,90,55}; 

extern uint8_t duty;
extern uint8_t high_temperature;
extern uint8_t low_temperature;
void main()
{
    uint8_t temp_value = 0;     // 存放临时变量
    hd7279a_init();
    ds18b20_init();
    menu_init();
    ds18b20_read_temperature(&temperature);
    Timer0_Init();
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
                if(now_menu_index == PA_RUN_SET_MENU_ID)
                {
                    temp_value = motor_test[pa_select_index];
                }
                if(now_menu_index == PA_CON_SET_B_MENU_ID)
                {
                    temp_value = low_temperature;
                }
                if(now_menu_index == PA_CON_SET_F_MENU_ID)
                {
                    temp_value = high_temperature;
                }
            }
            break;        
        }
        if(now_menu_index != last_menu_index)
        {
            EA = 0;
            display_clear();
            menu_list[now_menu_index].current_menu();
            last_menu_index = now_menu_index;
            EA = 1;
        }
        Delay10ms();
        if((now_menu_index != MOTOR_SPEED_PARAM_MENU_ID)&&(now_menu_index != MOTOR_RUN_MENU_ID))
        {
            duty = 0;
        }
        if(now_menu_index == TEMP_PARAM_MENU_ID)
		{
			EA = 0;
			ds18b20_read_temperature(&temperature);
            display_clear();
			TEMP_PARAM_MENU();
			EA = 1;
		}
        if(now_menu_index == MOTOR_SPEED_PARAM_MENU_ID)
        {
			EA = 0;
			ds18b20_read_temperature(&temperature);
            temperature_to_pwm(temperature,&duty);
            display_clear();
			MOTOR_SPEED_PARAM_MENU();
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
        if(now_menu_index == PA_RUN_SELECT_MENU_ID)
        {
            switch (key_value)
            {
            case KEY_UP:
                pa_select_index++;
                if (pa_select_index > 10)
                {
                    pa_select_index = 1;
                }
                EA = 0;
                display_clear();
                PA_RUN_SELECT_MENU();
                EA = 1;
                break;
            case KEY_DOWN:
                pa_select_index--;
                if(pa_select_index < 1)
                {
                    pa_select_index = 10;
                }
                EA = 0;
                display_clear();
                PA_RUN_SELECT_MENU();
                EA = 1;
                break;
            }
        }
        if(now_menu_index == PA_RUN_SET_MENU_ID)
        {
            switch (key_value)
            {
            case KEY_UP:
                motor_test[pa_select_index]++;
                if (motor_test[pa_select_index] > 99)
                {
                    motor_test[pa_select_index] = 99;
                }
                EA = 0;
                display_clear();
                PA_RUN_SET_MENU();
                EA = 1;
                break;
            case KEY_DOWN:
                motor_test[pa_select_index]--;
                if(motor_test[pa_select_index] < 0)
                {
                    motor_test[pa_select_index] = 0;
                }
                EA = 0;
                display_clear();
                PA_RUN_SET_MENU();
                EA = 1;
                break;
            case KEY_BACK:
                motor_test[pa_select_index] = temp_value;
                EA = 0;
                display_clear();
                PA_RUN_SET_MENU();
                EA = 1;
                break;
            }            
        }
        if(now_menu_index == PA_CON_SET_B_MENU_ID)
        {
            switch (key_value)
            {
            case KEY_UP:
                low_temperature++;
                if (low_temperature > 99)
                {
                    low_temperature = 99;
                }
                EA = 0;
                display_clear();
                PA_CON_SET_B_MENU();
                EA = 1;
                break;
            case KEY_DOWN:
                low_temperature--;
                if(low_temperature < 0)
                {
                    low_temperature = 0;
                }
                EA = 0;
                display_clear();
                PA_CON_SET_B_MENU();
                EA = 1;
                break;
            case KEY_BACK:
                low_temperature = temp_value;
                EA = 0;
                display_clear();
                PA_CON_SET_B_MENU();
                EA = 1;
                break;
            }            
        }
        if(now_menu_index == PA_CON_SET_F_MENU_ID)
        {
            switch (key_value)
            {
            case KEY_UP:
                high_temperature++;
                if (high_temperature > 99)
                {
                    high_temperature = 99;
                }
                EA = 0;
                display_clear();
                PA_CON_SET_F_MENU();
                EA = 1;
                break;
            case KEY_DOWN:
                high_temperature--;
                if(high_temperature < 0)
                {
                    high_temperature = 0;
                }
                EA = 0;
                display_clear();
                PA_CON_SET_F_MENU();
                EA = 1;
                break;
            case KEY_BACK:
                high_temperature = temp_value;
                EA = 0;
                display_clear();
                PA_CON_SET_F_MENU();
                EA = 1;
                break;
            }            
        }         
    }
}

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}