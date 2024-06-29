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

extern code Menu_t menu_list[16];

// �ղ˵����
#define NULL_MENU_ID          255

/* һ���˵� */
// �¶ȼ��˵����
#define TEMP_MENU_ID          0
// ������Բ˵����
#define MOTOR_MENU_ID         1
// ������ٲ˵����
#define MOTOR_SPEED_MENU_ID   2
// �������òҵ����
#define PARAM_SET_MENU_ID     3

/* �����˵� */
// �¶Ȳ����˵����
#define TEMP_PARAM_MENU_ID    4
// ������Թ��ղ˵����
#define MOTOR_SELECT_MENU_ID  5
// ������ٲ����˵����
#define MOTOR_SPEED_PARAM_MENU_ID  6
// ������ٲ˵����
#define PA_RUN_MENU_ID  7
// ������ٲ˵����
#define PA_CON_MENU_ID  8



// ������в˵����
#define MOTOR_RUN_MENU_ID     9
// �������ѡ��˵����
#define PA_RUN_SELECT_MENU_ID 10
// �������ѡ��˵����
#define PA_CON_SELECT_B_MENU_ID 11
#define PA_CON_SELECT_F_MENU_ID 12


// ����������ò˵����
#define PA_RUN_SET_MENU_ID    13
// ����������ò˵����
#define PA_CON_SET_B_MENU_ID    14
#define PA_CON_SET_F_MENU_ID    15


void menu_init(void);
void TEMP_PARAM_MENU(void);
void MOTOR_SELECT_MENU(void);
void MOTOR_SPEED_PARAM_MENU(void);
void PA_RUN_SELECT_MENU(void);
void PA_RUN_SET_MENU(void);
void PA_CON_SET_B_MENU(void);
void PA_CON_SET_F_MENU(void);
#endif  // __MENU_H__
