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

// �ղ˵����
#define NULL_MENU_ID          255
// �¶ȼ��˵����
#define TEMP_MENU_ID          0
// ������Բ˵����
#define MOTOR_MENU_ID         1
// ������ٲ˵����
#define MOTOR_SPEED_MENU_ID   2
// �������òҵ����
#define PARAM_SET_MENU_ID     3
// �¶Ȳ����˵����
#define TEMP_PARAM_MENU_ID    4
// ������Թ��ղ˵����
#define MOTOR_TEST_MENU_ID    5
// ������в˵����
#define MOTOR_RUN_MENU_ID     6
// ������ٲ����˵����
#define MOTOR_SPEED_PARAM_MENU_ID     7
#endif  // __MENU_H__
