#include "menu.h"
#include "bsp_display.h"
#include "algorithm.h"

extern int8_t input_password[4];

code Menu_t menu_list[22] = {
    /* 一级菜单 */
    {TEMP_MENU_ID, MOTOR_MENU_ID, PID_MENU_ID, TEMP_PARAM_MENU_ID, NULL_MENU_ID, TEMP_MENU},
    {MOTOR_MENU_ID, MOTOR_SPEED_MENU_ID, TEMP_MENU_ID, MOTOR_SELECT_MENU_ID, NULL_MENU_ID, MOTOR_MENU},
    {MOTOR_SPEED_MENU_ID, PARAM_SET_MENU_ID, MOTOR_MENU_ID, MOTOR_SPEED_PARAM_MENU_ID, NULL_MENU_ID, MOTOR_SPEED_MENU},
    {PARAM_SET_MENU_ID, PID_MENU_ID, MOTOR_SPEED_MENU_ID, PA_RUN_MENU_ID, NULL_MENU_ID, PARAM_SET_MENU},
    {PID_MENU_ID, TEMP_MENU_ID, PARAM_SET_MENU_ID, PID_CONTROL_MENU_ID, NULL_MENU_ID, PID_MENU},
    /* 二级菜单 */
    {TEMP_PARAM_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, TEMP_MENU_ID, TEMP_PARAM_MENU},
    {MOTOR_SELECT_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, MOTOR_RUN_MENU_ID, MOTOR_MENU_ID, MOTOR_SELECT_MENU},
    {MOTOR_SPEED_PARAM_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, MOTOR_SPEED_MENU_ID, MOTOR_SPEED_PARAM_MENU},
    {PA_RUN_MENU_ID, PA_CON_MENU_ID, PA_PID_MENU_ID, PA_RUN_SELECT_MENU_ID, PARAM_SET_MENU_ID, MOTOR_RUN_SET_MENU},
    {PA_CON_MENU_ID, PA_PID_MENU_ID, PA_RUN_MENU_ID, PA_CON_SELECT_B_MENU_ID, PARAM_SET_MENU_ID, MOTOR_CON_SET_MENU},
    {PA_PID_MENU_ID, PA_RUN_MENU_ID, PA_CON_MENU_ID, PA_PID_PASSWORD_MENU_ID, PARAM_SET_MENU_ID, PA_PID_MENU},
    {PID_CONTROL_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PID_MENU_ID, PID_CONTROL_MENU},
    /* 三级菜单 */
    {MOTOR_RUN_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, MOTOR_SELECT_MENU_ID, MOTOR_RUN_MENU},
    {PA_RUN_SELECT_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_RUN_SET_MENU_ID, PA_RUN_MENU_ID, PA_RUN_SELECT_MENU},
    {PA_CON_SELECT_B_MENU_ID, PA_CON_SELECT_F_MENU_ID, PA_CON_SELECT_F_MENU_ID, PA_CON_SET_B_MENU_ID, PA_CON_MENU_ID, PA_CON_SELECT_B_MENU},
    {PA_CON_SELECT_F_MENU_ID, PA_CON_SELECT_B_MENU_ID, PA_CON_SELECT_B_MENU_ID, PA_CON_SET_F_MENU_ID, PA_CON_MENU_ID, PA_CON_SELECT_F_MENU},
    {PA_PID_PASSWORD_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_PID_SET_TARGET_MENU_ID, NULL_MENU_ID, PA_PID_PASSWORD_MENU},

    /* 四级菜单 */
    {PA_RUN_SET_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_RUN_SELECT_MENU_ID, NULL_MENU_ID, PA_RUN_SET_MENU},
    {PA_CON_SET_B_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_CON_SELECT_B_MENU_ID, NULL_MENU_ID, PA_CON_SET_B_MENU},
    {PA_CON_SET_F_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_CON_SELECT_F_MENU_ID, NULL_MENU_ID, PA_CON_SET_F_MENU},
    {PA_PID_SET_TARGET_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_PID_MENU_ID, NULL_MENU_ID, PA_PID_SET_TARGET_MENU},
    {PA_PID_PASSWORD_ERROR_MENU_ID, NULL_MENU_ID, NULL_MENU_ID, PA_PID_MENU_ID, NULL_MENU_ID, PA_PID_PASSWORD_ERROR_MENU},
};

extern uint8_t duty;
extern uint16_t temperature;
extern uint8_t select_index;
extern uint8_t pa_select_index;
extern int8_t motor_test[11];
extern int8_t high_temperature;
extern int8_t low_temperature;
extern PID_t pid_temperature;

void menu_init(void)
{
    TEMP_MENU();
}

void TEMP_MENU(void)
{
    display_digit(DIGIT_4, 0xA9, 0); // t
    display_digit(DIGIT_5, 0xF1, 0); // P
    display_digit(DIGIT_6, 0x01, 0); // -
}

void TEMP_PARAM_MENU(void)
{
    uint8_t dat[4] = {0};
    uint16_t temp  = 0;
    temp           = (uint16_t)((float)temperature * 6.25);
    display_digit(DIGIT_4, 0xA9, 0); // t
    display_digit(DIGIT_5, 0xF1, 0); // P
    display_digit(DIGIT_6, 0x01, 0); // -
    dat[0] = temp / 1000;
    dat[1] = temp % 1000 / 100;
    dat[2] = temp % 100 / 10;
    dat[3] = temp % 10;
    display_digit(DIGIT_0, digit_array[dat[0]], 0);
    display_digit(DIGIT_1, digit_array[dat[1]], 1);
    display_digit(DIGIT_2, digit_array[dat[2]], 0);
    display_digit(DIGIT_3, digit_array[dat[3]], 0);
}

void MOTOR_MENU(void)
{
    display_digit(DIGIT_4, 0x21, 0); // r
    display_digit(DIGIT_5, 0x2C, 0); // u
    display_digit(DIGIT_6, 0x25, 0); // n
    display_digit(DIGIT_7, 0x01, 0); // -
}
void MOTOR_SELECT_MENU(void)
{
    uint8_t dat[3] = {0};
    dat[0]         = motor_test[select_index] / 100;
    dat[1]         = motor_test[select_index] % 100 / 10;
    dat[2]         = motor_test[select_index] % 10;
    display_digit(DIGIT_4, 0x21, 0); // r
    display_digit(DIGIT_5, 0x01, 0); // -
    if (select_index == 10) {
        display_digit(DIGIT_6, digit_array[1], 0);
        display_digit(DIGIT_7, digit_array[0], 0);
    } else {
        display_digit(DIGIT_7, digit_array[select_index], 0);
    }
    if (dat[0]) {
        display_digit(DIGIT_1, digit_array[1], 0);
    }
    if (dat[1] || dat[0]) {
        display_digit(DIGIT_2, digit_array[dat[1]], 0);
    }
    display_digit(DIGIT_3, digit_array[dat[2]], 0);
}

void MOTOR_RUN_MENU(void)
{
    uint8_t dat[3] = 0;
    dat[0]         = motor_test[select_index] / 100;
    dat[1]         = motor_test[select_index] % 100 / 10;
    dat[2]         = motor_test[select_index] % 10;
    display_digit(DIGIT_4, 0x21, 0); // r
    display_digit(DIGIT_5, 0x2C, 0); // u
    display_digit(DIGIT_6, 0x25, 0); // n
    display_digit(DIGIT_7, 0x01, 0); // -
    if (dat[0]) {
        display_digit(DIGIT_2, digit_array[1], 0);
    }
    if (dat[1] || dat[0]) {
        display_digit(DIGIT_2, digit_array[dat[1]], 0);
    }
    display_digit(DIGIT_3, digit_array[dat[2]], 0);
    duty = motor_test[select_index];
}

void MOTOR_SPEED_MENU(void)
{
    display_digit(DIGIT_4, 0xB8, 0); // C
    display_digit(DIGIT_5, 0x2D, 0); // o
    display_digit(DIGIT_6, 0x25, 0); // n
    display_digit(DIGIT_7, 0x01, 0); // -
}

void MOTOR_SPEED_PARAM_MENU(void)
{
    uint8_t dat[7] = {0};
    uint16_t temp  = 0;
    temp           = (uint16_t)((float)temperature * 6.25);
    dat[0]         = temp / 1000;
    dat[1]         = temp % 1000 / 100;
    dat[2]         = temp % 100 / 10;
    dat[3]         = temp % 10;
    display_digit(DIGIT_4, digit_array[dat[0]], 0);
    display_digit(DIGIT_5, digit_array[dat[1]], 1);
    display_digit(DIGIT_6, digit_array[dat[2]], 0);
    display_digit(DIGIT_7, digit_array[dat[3]], 0);
    dat[4] = duty / 100;
    dat[5] = duty % 100 / 10;
    dat[6] = duty % 10;
    if (dat[4]) {
        display_digit(DIGIT_1, digit_array[1], 0);
    }
    if (dat[4] || dat[5]) {
        display_digit(DIGIT_2, digit_array[dat[5]], 0);
    }
    display_digit(DIGIT_3, digit_array[dat[6]], 0);
}

void PARAM_SET_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0xF5, 0); // A
    display_digit(DIGIT_7, 0x01, 0); // -
}

void MOTOR_RUN_SET_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0xF5, 0); // A
    display_digit(DIGIT_7, 0x01, 0); // -

    display_digit(DIGIT_1, 0x21, 0); // r
    display_digit(DIGIT_2, 0x2C, 0); // u
    display_digit(DIGIT_3, 0x25, 0); // n
}

void MOTOR_CON_SET_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0xF5, 0); // A
    display_digit(DIGIT_7, 0x01, 0); // -

    display_digit(DIGIT_1, 0xB8, 0); // C
    display_digit(DIGIT_2, 0x2D, 0); // o
    display_digit(DIGIT_3, 0x25, 0); // n
}

void PA_RUN_SELECT_MENU(void)
{
    uint8_t dat[3] = 0;
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0x01, 0); // -
    dat[0] = motor_test[pa_select_index] / 100;
    dat[1] = motor_test[pa_select_index] % 100 / 10;
    dat[2] = motor_test[pa_select_index] % 10;
    if (pa_select_index == 10) {
        display_digit(DIGIT_6, digit_array[1], 0);
        display_digit(DIGIT_7, digit_array[0], 0);
    } else {
        display_digit(DIGIT_7, digit_array[pa_select_index], 0);
    }
    if (dat[0]) {
        display_digit(DIGIT_1, digit_array[1], 0);
    }
    if (dat[1] || dat[0]) {
        display_digit(DIGIT_2, digit_array[dat[1]], 0);
    }
    display_digit(DIGIT_3, digit_array[dat[2]], 0);
}

void PA_CON_SELECT_B_MENU(void)
{
    uint8_t dat[2] = {0};
    dat[0]         = low_temperature / 10;
    dat[1]         = low_temperature % 10;
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0xF5, 0); // A
    display_digit(DIGIT_6, 0x01, 0); // -
    display_digit(DIGIT_7, 0xAD, 0); // b
    display_digit(DIGIT_2, digit_array[dat[0]], 0);
    display_digit(DIGIT_3, digit_array[dat[1]], 0);
}

void PA_CON_SELECT_F_MENU(void)
{
    uint8_t dat[2] = {0};
    dat[0]         = high_temperature / 10;
    dat[1]         = high_temperature % 10;
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0xF5, 0); // A
    display_digit(DIGIT_6, 0x01, 0); // -
    display_digit(DIGIT_7, 0xB1, 0); // f
    display_digit(DIGIT_2, digit_array[dat[0]], 0);
    display_digit(DIGIT_3, digit_array[dat[1]], 0);
}

void PA_CON_SET_B_MENU(void)
{
    uint8_t dat[2] = {0};
    dat[0]         = low_temperature / 10;
    dat[1]         = low_temperature % 10;
    display_digit(DIGIT_4, 0xF5, 0); // A
    display_digit(DIGIT_5, 0x01, 0); // -
    display_digit(DIGIT_7, 0xAD, 0); // b
    display_digit(DIGIT_2, digit_array[dat[0]], 0);
    display_digit(DIGIT_3, digit_array[dat[1]], 0);
}
void PA_CON_SET_F_MENU(void)
{
    uint8_t dat[2] = {0};
    dat[0]         = high_temperature / 10;
    dat[1]         = high_temperature % 10;
    display_digit(DIGIT_4, 0xF5, 0); // A
    display_digit(DIGIT_5, 0x01, 0); // -
    display_digit(DIGIT_7, 0xB1, 0); // f
    display_digit(DIGIT_2, digit_array[dat[0]], 0);
    display_digit(DIGIT_3, digit_array[dat[1]], 0);
}
void PA_RUN_SET_MENU(void)
{
    uint8_t dat[3] = 0;
    dat[0]         = motor_test[pa_select_index] / 100;
    dat[1]         = motor_test[pa_select_index] % 100 / 10;
    dat[2]         = motor_test[pa_select_index] % 10;
    display_digit(DIGIT_4, 0xF5, 0); // A
    display_digit(DIGIT_5, 0x01, 0); // -
    if (pa_select_index == 10) {
        display_digit(DIGIT_6, digit_array[1], 0);
        display_digit(DIGIT_7, digit_array[0], 0);
    } else {
        display_digit(DIGIT_7, digit_array[pa_select_index], 0);
    }
    if (dat[0]) {
        display_digit(DIGIT_1, digit_array[1], 0);
    }
    if (dat[1] || dat[0]) {
        display_digit(DIGIT_2, digit_array[dat[1]], 0);
    }
    display_digit(DIGIT_3, digit_array[dat[2]], 0);
}

void PID_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0x44, 0); // I
    display_digit(DIGIT_6, 0x6D, 0); // d
    display_digit(DIGIT_7, 0x01, 0); // -
}

void PID_CONTROL_MENU(void)
{
    uint8_t dat[7] = {0};
    uint16_t temp  = 0;
    temp           = (uint16_t)((float)temperature * 6.25);
    dat[0]         = temp / 1000;
    dat[1]         = temp % 1000 / 100;
    dat[2]         = temp % 100 / 10;
    dat[3]         = temp % 10;
    display_digit(DIGIT_4, digit_array[dat[0]], 0);
    display_digit(DIGIT_5, digit_array[dat[1]], 1);
    display_digit(DIGIT_6, digit_array[dat[2]], 0);
    display_digit(DIGIT_7, digit_array[dat[3]], 0);
    dat[4] = duty / 100;
    dat[5] = duty % 100 / 10;
    dat[6] = duty % 10;
    if (dat[4]) {
        display_digit(DIGIT_1, digit_array[1], 0);
    }
    if (dat[4] || dat[5]) {
        display_digit(DIGIT_2, digit_array[dat[5]], 0);
    }
    display_digit(DIGIT_3, digit_array[dat[6]], 0);
}

void PA_PID_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0xF5, 0); // A
    display_digit(DIGIT_6, 0x01, 0); // -
    display_digit(DIGIT_1, 0xF1, 0); // P
    display_digit(DIGIT_2, 0x44, 0); // I
    display_digit(DIGIT_3, 0x6D, 0); // d
}

void PA_PID_PASSWORD_ERROR_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0x44, 0); // I
    display_digit(DIGIT_6, 0xF4, 0); // N

    display_digit(DIGIT_0, 0xB9, 0); // E
    display_digit(DIGIT_1, 0x21, 0); // r
    display_digit(DIGIT_2, 0x21, 0); // r
}

void PA_PID_PASSWORD_MENU(void)
{
    display_digit(DIGIT_4, 0xF1, 0); // P
    display_digit(DIGIT_5, 0x44, 0); // I
    display_digit(DIGIT_6, 0xF4, 0); // N

    display_digit(DIGIT_0, digit_array[input_password[0]], 0);
    display_digit(DIGIT_1, digit_array[input_password[1]], 0);
    display_digit(DIGIT_2, digit_array[input_password[2]], 0);
    display_digit(DIGIT_3, digit_array[input_password[3]], 0);
}

void PA_PID_SET_TARGET_MENU(void)
{
    uint16_t temp  = 0;
    uint8_t dat[3] = 0;
    temp           = (uint16_t)(pid_temperature.target * 10);
    dat[0]         = temp / 100;
    dat[1]         = temp % 100 / 10;
    dat[2]         = temp % 10;
    display_digit(DIGIT_4, 0xF5, 0); // A
    display_digit(DIGIT_5, 0x01, 0); // -
    display_digit(DIGIT_7, 0xF1, 0); // t
    display_digit(DIGIT_1, digit_array[dat[0]], 0);
    display_digit(DIGIT_2, digit_array[dat[1]], 1);
    display_digit(DIGIT_3, digit_array[dat[2]], 0);
}
