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
}Menu_t;

extern code Menu_t menu_list[20];

// 空菜单编号
#define NULL_MENU_ID          255

/* 一级菜单 */
// 温度检测菜单编号
#define TEMP_MENU_ID               0
// 电机测试菜单编号
#define MOTOR_MENU_ID              1
// 电机调速菜单编号
#define MOTOR_SPEED_MENU_ID        2
// 参数设置菜单编号
#define PARAM_SET_MENU_ID          3
// PID控制菜单编号
#define PID_MENU_ID                4

/* 二级菜单 */
// 温度参数菜单编号
#define TEMP_PARAM_MENU_ID         5
// 电机测试工艺菜单编号
#define MOTOR_SELECT_MENU_ID       6
// 电机调速参数菜单编号
#define MOTOR_SPEED_PARAM_MENU_ID  7
// 电机测速菜单编号
#define PA_RUN_MENU_ID             8
// 电机调速菜单编号
#define PA_CON_MENU_ID             9
// PID参数设置菜单编号
#define PA_PID_MENU_ID             10
// PID控制菜单编号
#define PID_CONTROL_MENU_ID        11


// 电机运行菜单编号
#define MOTOR_RUN_MENU_ID          12
// 电机测速选择菜单编号
#define PA_RUN_SELECT_MENU_ID      13
// 电机调速选择菜单编号
#define PA_CON_SELECT_B_MENU_ID    14
#define PA_CON_SELECT_F_MENU_ID    15

#define PA_PID_SET_MENU_ID         16

// 电机测速设置菜单编号
#define PA_RUN_SET_MENU_ID         17
// 电机调速设置菜单编号
#define PA_CON_SET_B_MENU_ID       18
#define PA_CON_SET_F_MENU_ID       19


void menu_init(void);
void TEMP_PARAM_MENU(void);
void MOTOR_SELECT_MENU(void);
void MOTOR_SPEED_PARAM_MENU(void);
void PA_RUN_SELECT_MENU(void);
void PA_RUN_SET_MENU(void);
void PA_CON_SET_B_MENU(void);
void PA_CON_SET_F_MENU(void);
void PID_CONTROL_MENU(void);
void PA_PID_SET_MENU(void);
#endif  // __MENU_H__
