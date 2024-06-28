#include "menu.h"
#include "bsp_display.h"

static void TEMP_MENU(void);

static void MOTOR_MENU(void);
static void MOTOR_RUN_MENU(void);

static void MOTOR_SPEED_MENU(void);
static void MOTOR_SPEED_PARAM_MENU(void);

static void PARAM_SET_MENU(void);

code Menu_t menu_list[10] = {
    /* 一级菜单 */
    {TEMP_MENU_ID,MOTOR_MENU_ID,PARAM_SET_MENU_ID,TEMP_PARAM_MENU_ID,NULL_MENU_ID,TEMP_MENU},
    {MOTOR_MENU_ID,MOTOR_SPEED_MENU_ID,TEMP_MENU_ID,MOTOR_SELECT_MENU_ID,NULL_MENU_ID,MOTOR_MENU},
    {MOTOR_SPEED_MENU_ID,PARAM_SET_MENU_ID,MOTOR_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,MOTOR_SPEED_MENU},
    {PARAM_SET_MENU_ID,TEMP_MENU_ID,MOTOR_SPEED_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,PARAM_SET_MENU},
    /* 二级菜单 */
    {TEMP_PARAM_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,TEMP_MENU_ID,TEMP_PARAM_MENU},
    {MOTOR_SELECT_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,MOTOR_RUN_MENU_ID,MOTOR_MENU_ID,MOTOR_SELECT_MENU},
    // {MOTOR_SPEED_PARAM_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,MOTOR_SPEED_MENU_ID,MOTOR_SPEED_PARAM_MENU},
    // /* 三级菜单 */
    {MOTOR_RUN_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,NULL_MENU_ID,MOTOR_SELECT_MENU_ID,MOTOR_RUN_MENU},
};

extern uint16_t temperature;
extern uint8_t select_index;
extern uint8_t motor_test[11];

void menu_init(void)
{
    TEMP_MENU();
}

static void TEMP_MENU(void)
{
    display_digit(DIGIT_4,0xA9,0);
    display_digit(DIGIT_5,0xF1,0);
    display_digit(DIGIT_6,0x01,0);
}

void TEMP_PARAM_MENU(void)
{
    uint8_t dat[4] = {0};
    uint16_t temp = 0;
    temp = (uint16_t)((float)temperature * 6.25);
    display_digit(DIGIT_4,0xA9,0);
    display_digit(DIGIT_5,0xF1,0);
    display_digit(DIGIT_6,0x01,0);
    dat[0] = temp / 1000;
    dat[1] = temp % 1000  / 100;
    dat[2] = temp % 100   / 10;
    dat[3] = temp % 10;
    display_digit(DIGIT_0,digit_array[dat[0]],0);
    display_digit(DIGIT_1,digit_array[dat[1]],1);
    display_digit(DIGIT_2,digit_array[dat[2]],0);
    display_digit(DIGIT_3,digit_array[dat[3]],0);
}

static void MOTOR_MENU(void)
{
    display_digit(DIGIT_4,0x21,0);
    display_digit(DIGIT_5,0x2C,0);
    display_digit(DIGIT_6,0x25,0);
    display_digit(DIGIT_7,0x01,0);   
}
void MOTOR_SELECT_MENU(void)
{
    uint8_t dat[2] = 0;
    dat[0] = motor_test[select_index] / 10;
    dat[1] = motor_test[select_index] % 10;
    display_digit(DIGIT_4,0x21,0);
    display_digit(DIGIT_5,0x01,0);
    if(select_index == 10)
    {
        display_digit(DIGIT_6,digit_array[1],0);
        display_digit(DIGIT_7,digit_array[0],0);
    }
    else
    {
        display_digit(DIGIT_7,digit_array[select_index],0);
    }
    
    display_digit(DIGIT_2,digit_array[dat[0]],0);
    display_digit(DIGIT_3,digit_array[dat[1]],0);
}

static void MOTOR_RUN_MENU(void)
{
    uint8_t dat[2] = 0;
    dat[0] = motor_test[select_index] / 10;
    dat[1] = motor_test[select_index] % 10;
    display_digit(DIGIT_4,0x21,0);
    display_digit(DIGIT_5,0x2C,0);
    display_digit(DIGIT_6,0x25,0);
    display_digit(DIGIT_7,0x01,0);
    
    display_digit(DIGIT_2,digit_array[dat[0]],0);
    display_digit(DIGIT_3,digit_array[dat[1]],0);     
}

static void MOTOR_SPEED_MENU(void)
{
    display_digit(DIGIT_4,0xB8,0);
    display_digit(DIGIT_5,0x2D,0);
    display_digit(DIGIT_6,0x25,0);
    display_digit(DIGIT_7,0x01,0);      
}

static void MOTOR_SPEED_PARAM_MENU(void)
{

}

static void PARAM_SET_MENU(void)
{
    display_digit(DIGIT_4,0xF1,0);
    display_digit(DIGIT_5,0xF5,0);
    display_digit(DIGIT_7,0x01,0);      
}