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

// �ղ˵����
#define NULL_MENU_ID 255

/* һ���˵� */
// �¶ȼ��˵����
#define TEMP_MENU_ID 0
// ������Բ˵����
#define MOTOR_MENU_ID 1
// ������ٲ˵����
#define MOTOR_SPEED_MENU_ID 2
// �������ò˵����
#define PARAM_SET_MENU_ID 3
// PID���Ʋ˵����
#define PID_MENU_ID 4

void TEMP_MENU(void);
void MOTOR_MENU(void);
void MOTOR_SPEED_MENU(void);
void PARAM_SET_MENU(void);
void PID_MENU(void);

/* �����˵� */
// �¶Ȳ����˵����
#define TEMP_PARAM_MENU_ID 5
// ������Թ��ղ˵����
#define MOTOR_SELECT_MENU_ID 6
// ������ٲ����˵����
#define MOTOR_SPEED_PARAM_MENU_ID 7
// ������ٲ˵����
#define PA_RUN_MENU_ID 8
// ������ٲ˵����
#define PA_CON_MENU_ID 9
// PID�������ò˵����
#define PA_PID_MENU_ID 10
// PID���Ʋ˵����
#define PID_CONTROL_MENU_ID 11

void TEMP_PARAM_MENU(void);
void MOTOR_SELECT_MENU(void);
void MOTOR_SPEED_PARAM_MENU(void);
void MOTOR_RUN_SET_MENU(void);
void MOTOR_CON_SET_MENU(void);
void PA_PID_MENU(void);
void PID_CONTROL_MENU(void);

/* �����˵� */
// ������в˵����
#define MOTOR_RUN_MENU_ID 12
// �������ѡ��˵����
#define PA_RUN_SELECT_MENU_ID 13
// �����������ѡ��˵����
#define PA_CON_SELECT_B_MENU_ID 14
// �����������ѡ��˵����
#define PA_CON_SELECT_F_MENU_ID 15
// PID������������˵�
#define PA_PID_PASSWORD_MENU_ID 16

void MOTOR_RUN_MENU(void);
void PA_RUN_SELECT_MENU(void);
void PA_CON_SELECT_B_MENU(void);
void PA_CON_SELECT_F_MENU(void);
void PA_PID_PASSWORD_MENU(void);

/* �ļ��˵� */
// ����������ò˵����
#define PA_RUN_SET_MENU_ID 17
// ��������������ò˵����
#define PA_CON_SET_B_MENU_ID 18
// ��������������ò˵����
#define PA_CON_SET_F_MENU_ID 19
// PID target ����ѡ��˵����
#define PA_PID_SET_TARGET_MENU_ID 20
// PID target ����ѡ��˵����
#define PA_PID_SET_TARGET_MENU_ID 20
// PID �������ô���˵�
#define PA_PID_PASSWORD_ERROR_MENU_ID 21

void PA_RUN_SET_MENU(void);
void PA_CON_SET_B_MENU(void);
void PA_CON_SET_F_MENU(void);
void PA_PID_SET_TARGET_MENU(void);
void PA_PID_PASSWORD_ERROR_MENU(void);

void menu_init(void);
#endif // __MENU_H__
