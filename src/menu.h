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

extern code Menu_t menu_list[10];

// 空菜单编号
#define NULL_MENU_ID          255

/* 一级菜单 */
// 温度检测菜单编号
#define TEMP_MENU_ID          0
// 电机测试菜单编号
#define MOTOR_MENU_ID         1
// 电机调速菜单编号
#define MOTOR_SPEED_MENU_ID   2
// 参数设置惨淡编号
#define PARAM_SET_MENU_ID     3

/* 二级菜单 */
// 温度参数菜单编号
#define TEMP_PARAM_MENU_ID    4
// 电机测试工艺菜单编号
#define MOTOR_SELECT_MENU_ID  5
// 电机运行菜单编号
#define MOTOR_RUN_MENU_ID     6


// 电机调速参数菜单编号
#define MOTOR_SPEED_PARAM_MENU_ID     7

void menu_init(void);
void TEMP_PARAM_MENU(void);
void MOTOR_SELECT_MENU(void);
#endif  // __MENU_H__
