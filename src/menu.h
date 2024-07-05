#ifndef __MENU_H__
#define __MENU_H__
#include "main.h"

typedef struct
{
    uint8_t index;
    uint8_t up;
    uint8_t down;
    uint8_t enter;
    uint8_t back;
    void (*current_menu)();
} Menu_t;

extern code Menu_t menu_list[22];

// 空菜单编号
#define NULL_MENU_ID 255

/* 一级菜单 */
// 温度检测菜单编号
#define TEMP_MENU_ID 0
// 电机测试菜单编号
#define MOTOR_MENU_ID 1
// 电机调速菜单编号
#define MOTOR_SPEED_MENU_ID 2
// 参数设置菜单编号
#define PARAM_SET_MENU_ID 3
// PID控制菜单编号
#define PID_MENU_ID 4

void TEMP_MENU(void);
void MOTOR_MENU(void);
void MOTOR_SPEED_MENU(void);
void PARAM_SET_MENU(void);
void PID_MENU(void);

/* 二级菜单 */
// 温度参数菜单编号
#define TEMP_PARAM_MENU_ID 5
// 电机测试工艺菜单编号
#define MOTOR_SELECT_MENU_ID 6
// 电机调速参数菜单编号
#define MOTOR_SPEED_PARAM_MENU_ID 7
// 电机测速菜单编号
#define PA_RUN_MENU_ID 8
// 电机调速菜单编号
#define PA_CON_MENU_ID 9
// PID参数设置菜单编号
#define PA_PID_MENU_ID 10
// PID控制菜单编号
#define PID_CONTROL_MENU_ID 11

void TEMP_PARAM_MENU(void);
void MOTOR_SELECT_MENU(void);
void MOTOR_SPEED_PARAM_MENU(void);
void MOTOR_RUN_SET_MENU(void);
void MOTOR_CON_SET_MENU(void);
void PA_PID_MENU(void);
void PID_CONTROL_MENU(void);

/* 三级菜单 */
// 电机运行菜单编号
#define MOTOR_RUN_MENU_ID 12
// 电机测速选择菜单编号
#define PA_RUN_SELECT_MENU_ID 13
// 电机调速下限选择菜单编号
#define PA_CON_SELECT_B_MENU_ID 14
// 电机调速上限选择菜单编号
#define PA_CON_SELECT_F_MENU_ID 15
// PID参数设置密码菜单
#define PA_PID_PASSWORD_MENU_ID 16

void MOTOR_RUN_MENU(void);
void PA_RUN_SELECT_MENU(void);
void PA_CON_SELECT_B_MENU(void);
void PA_CON_SELECT_F_MENU(void);
void PA_PID_PASSWORD_MENU(void);

/* 四级菜单 */
// 电机测速设置菜单编号
#define PA_RUN_SET_MENU_ID 17
// 电机调速上限设置菜单编号
#define PA_CON_SET_B_MENU_ID 18
// 电机调速下限设置菜单编号
#define PA_CON_SET_F_MENU_ID 19
// PID target 参数选择菜单编号
#define PA_PID_SET_TARGET_MENU_ID 20
// PID target 参数选择菜单编号
#define PA_PID_SET_TARGET_MENU_ID 20
// PID 密码设置错误菜单
#define PA_PID_PASSWORD_ERROR_MENU_ID 21

void PA_RUN_SET_MENU(void);
void PA_CON_SET_B_MENU(void);
void PA_CON_SET_F_MENU(void);
void PA_PID_SET_TARGET_MENU(void);
void PA_PID_PASSWORD_ERROR_MENU(void);

void menu_init(void);
#endif // __MENU_H__
