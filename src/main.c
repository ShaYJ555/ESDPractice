#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_eeprom.h"
#include "bsp_display.h"
#include "hd7279a.h"

#include "main.h"
#include "menu.h"
#include "interrupt.h"
#include "algorithm.h"

// ���ڿ������ֳ����̰�ʱ��
#define KEY_LONG_TIME 5

// �����ڹر����жϣ���ֹ�жϴ���ͨ��ʱ��
#define ENABLE_GLOBAL_INTERRUPT() \
    do {                          \
        EA = 1;                   \
    } while (0)
#define DISABLE_GLOBAL_INTERRUPT() \
    do {                           \
        EA = 0;                    \
    } while (0)

// ����������ʱ
static void Delay10ms(void);

uint16_t temperature;
uint8_t select_index                = 1;
uint8_t pa_select_index             = 1;
PID_t pid_temperature               = {0};
uint16_t high_temperature_cnt       = 0; // �����ж��Ƿ񳤶̰�
uint16_t low_temperature_cnt        = 0; // �����ж��Ƿ񳤶̰�
uint16_t motor_test_set_cnt         = 0; // �����ж��Ƿ񳤶̰�
uint16_t pid_temperature_target_cnt = 0; // �����ж��Ƿ񳤶̰�
int8_t motor_test[11]               = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 55};

uint8_t duty = 0;               // ����ٶ�ռ�ձ�
extern int8_t high_temperature; // ������ٲ˵��¶�����
extern int8_t low_temperature;  // ������ٲ˵��¶�����

/*
EEPROM ��������table
---------------------------------------------
|         ������                 | ��ַ |��С|
|--------------------------------------------
|uint8_t high_temperature       | 0x00 |  1 |
|uint8_t low_temperature        | 0x01 |  1 |
|float   pid_temperature.target | 0x02 |  2 |
|uint8_t motor_test             | 0x10 | 11 |
---------------------------------------------
*/

void main()
{
    uint8_t temp_value      = 0;   // �����ʱ����
    float float_temp_value  = 0.0; // �����ʱ����
    uint8_t key_value       = 0;   // ����ֵ
    uint8_t last_menu_index = 0;   // ���ڲ˵��л�
    uint8_t now_menu_index  = 0;
    hd7279a_init();
    ds18b20_init();
    menu_init();
    ds18b20_read_temperature(&temperature);
    pid_init(&pid_temperature);

    // // ��һ����¼���ȸ�EEPROM���
    // eeprom_read_bytes(0x01,&low_temperature,1);
    // eeprom_read_bytes(0x00,&high_temperature,1);
    // eeprom_read_bytes(0x02,&pid_temperature.target,sizeof(float));
    // eeprom_read_bytes(0x10,motor_test,11);
    // ������ȡ
    eeprom_read_bytes(0x01, &low_temperature, 1);
    eeprom_read_bytes(0x00, &high_temperature, 1);
    eeprom_read_bytes(0x02, (uint8_t *)&pid_temperature.target, sizeof(float));
    eeprom_read_bytes(0x10, motor_test, 11);

    Timer0_Init();
    while (1) {
        DISABLE_GLOBAL_INTERRUPT();
        key_value = key_scan();
        ENABLE_GLOBAL_INTERRUPT();
        switch (key_value) {
            case KEY_UP:
                if (menu_list[last_menu_index].up != NULL_MENU_ID) {
                    now_menu_index = menu_list[last_menu_index].up;
                }
                break;
            case KEY_DOWN:
                if (menu_list[last_menu_index].down != NULL_MENU_ID) {
                    now_menu_index = menu_list[last_menu_index].down;
                }
                break;
            case KEY_BACK:
                if (menu_list[last_menu_index].back != NULL_MENU_ID) {
                    now_menu_index = menu_list[last_menu_index].back;
                }
                break;
            case KEY_ENTER:
                if (menu_list[last_menu_index].enter != NULL_MENU_ID) {
                    now_menu_index = menu_list[last_menu_index].enter;
                    // ���룬��ȡ�����������ָ�����
                    if (now_menu_index == PA_RUN_SET_MENU_ID) {
                        temp_value = motor_test[pa_select_index];
                    }
                    if (now_menu_index == PA_CON_SET_B_MENU_ID) {
                        temp_value = low_temperature;
                    }
                    if (now_menu_index == PA_CON_SET_F_MENU_ID) {
                        temp_value = high_temperature;
                    }
                    if (now_menu_index == PA_PID_SET_MENU_ID) {
                        float_temp_value = pid_temperature.target;
                    }
                    //  �˳����������
                    if (last_menu_index == PA_CON_SET_B_MENU_ID) {
                        DISABLE_GLOBAL_INTERRUPT();
                        eeprom_write_bytes(0x01, &low_temperature, 1);
                        ENABLE_GLOBAL_INTERRUPT();
                    }
                    if (last_menu_index == PA_CON_SET_F_MENU_ID) {
                        DISABLE_GLOBAL_INTERRUPT();
                        eeprom_write_bytes(0x00, &high_temperature, 1);
                        ENABLE_GLOBAL_INTERRUPT();
                    }
                    if (last_menu_index == PA_PID_SET_MENU_ID) {
                        DISABLE_GLOBAL_INTERRUPT();
                        eeprom_write_bytes(0x02, (uint8_t *)&pid_temperature.target, sizeof(float));
                        ENABLE_GLOBAL_INTERRUPT();
                    }
                    if (last_menu_index == PA_RUN_SET_MENU_ID) {
                        DISABLE_GLOBAL_INTERRUPT();
                        eeprom_write_bytes(0x10 + pa_select_index, &motor_test[pa_select_index], 1);
                        ENABLE_GLOBAL_INTERRUPT();
                    }
                }
                break;
        }
        if (now_menu_index != last_menu_index) {
            DISABLE_GLOBAL_INTERRUPT();
            display_clear();
            menu_list[now_menu_index].current_menu();
            last_menu_index = now_menu_index;
            ENABLE_GLOBAL_INTERRUPT();
        }
        Delay10ms();
        if ((now_menu_index != MOTOR_SPEED_PARAM_MENU_ID) && (now_menu_index != MOTOR_RUN_MENU_ID)) {
            duty = 0;
        }
        if (now_menu_index == TEMP_PARAM_MENU_ID) {
            DISABLE_GLOBAL_INTERRUPT();
            ds18b20_read_temperature(&temperature);
            display_clear();
            TEMP_PARAM_MENU();
            ENABLE_GLOBAL_INTERRUPT();
        }
        if (now_menu_index == MOTOR_SPEED_PARAM_MENU_ID) {
            DISABLE_GLOBAL_INTERRUPT();
            ds18b20_read_temperature(&temperature);
            temperature_to_pwm(temperature, &duty);
            display_clear();
            MOTOR_SPEED_PARAM_MENU();
            ENABLE_GLOBAL_INTERRUPT();
        }
        if (now_menu_index == PID_CONTROL_MENU_ID) {
            DISABLE_GLOBAL_INTERRUPT();
            ds18b20_read_temperature(&temperature);
            pid_calculate(temperature, &pid_temperature);
            duty = pid_temperature.output;
            display_clear();
            PID_CONTROL_MENU();
            ENABLE_GLOBAL_INTERRUPT();
        }
        if (now_menu_index == MOTOR_SELECT_MENU_ID) {
            switch (key_value) {
                case KEY_UP:
                    select_index++;
                    if (select_index > 10) {
                        select_index = 1;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    MOTOR_SELECT_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_DOWN:
                    select_index--;
                    if (select_index < 1) {
                        select_index = 10;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    MOTOR_SELECT_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
            }
        }
        if (now_menu_index == PA_RUN_SELECT_MENU_ID) {
            switch (key_value) {
                case KEY_UP:
                    pa_select_index++;
                    if (pa_select_index > 10) {
                        pa_select_index = 1;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_RUN_SELECT_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_DOWN:
                    pa_select_index--;
                    if (pa_select_index < 1) {
                        pa_select_index = 10;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_RUN_SELECT_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
            }
        }
        if (now_menu_index == PA_RUN_SET_MENU_ID) {
            switch (key_value) {
                case KEY_UP:
                    motor_test_set_cnt++;
                    if (motor_test_set_cnt > KEY_LONG_TIME) {
                        motor_test[pa_select_index] += 5;
                    } else {
                        motor_test[pa_select_index]++;
                    }
                    if (motor_test[pa_select_index] > 100) {
                        motor_test[pa_select_index] = 100;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_RUN_SET_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_DOWN:
                    motor_test_set_cnt++;
                    if (motor_test_set_cnt > KEY_LONG_TIME) {
                        motor_test[pa_select_index] -= 5;
                    } else {
                        motor_test[pa_select_index]--;
                    }
                    if (motor_test[pa_select_index] < 0) {
                        motor_test[pa_select_index] = 0;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_RUN_SET_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_BACK:
                    motor_test[pa_select_index] = temp_value;
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_RUN_SET_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                default:
                    motor_test_set_cnt = 0;
                    break;
            }
        }
        if (now_menu_index == PA_CON_SET_B_MENU_ID) {
            switch (key_value) {
                case KEY_UP:
                    low_temperature_cnt++;
                    if (low_temperature_cnt > KEY_LONG_TIME) {
                        low_temperature += 5;
                    } else {
                        low_temperature++;
                    }
                    if (low_temperature > 99) {
                        low_temperature = 99;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_CON_SET_B_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_DOWN:
                    low_temperature_cnt++;
                    if (low_temperature_cnt > KEY_LONG_TIME) {
                        low_temperature -= 5;
                    } else {
                        low_temperature--;
                    }
                    if (low_temperature < 0) {
                        low_temperature = 0;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_CON_SET_B_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_BACK:
                    low_temperature = temp_value;
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_CON_SET_B_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                default:
                    low_temperature_cnt = 0;
                    break;
            }
        }
        if (now_menu_index == PA_CON_SET_F_MENU_ID) {
            switch (key_value) {
                case KEY_UP:
                    high_temperature_cnt++;
                    if (high_temperature_cnt > KEY_LONG_TIME) {
                        high_temperature += 5;
                    } else {
                        high_temperature++;
                    }
                    if (high_temperature > 99) {
                        high_temperature = 99;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_CON_SET_F_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_DOWN:
                    high_temperature_cnt++;
                    if (high_temperature_cnt > KEY_LONG_TIME) {
                        high_temperature -= 5;
                    } else {
                        high_temperature--;
                    }
                    if (high_temperature < 0) {
                        high_temperature = 0;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_CON_SET_F_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_BACK:
                    high_temperature = temp_value;
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_CON_SET_F_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                default:
                    high_temperature_cnt = 0;
                    break;
            }
        }
        if (now_menu_index == PA_PID_SET_MENU_ID) {
            switch (key_value) {
                case KEY_UP:
                    pid_temperature_target_cnt++;
                    if (pid_temperature_target_cnt > KEY_LONG_TIME) {
                        pid_temperature.target += 0.5;
                    } else {
                        pid_temperature.target += 0.1;
                    }
                    if (pid_temperature.target > 99) {
                        pid_temperature.target = 99;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_PID_SET_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_DOWN:
                    pid_temperature_target_cnt++;
                    if (pid_temperature_target_cnt > KEY_LONG_TIME) {
                        pid_temperature.target -= 0.5;
                    } else {
                        pid_temperature.target -= 0.1;
                    }
                    if (pid_temperature.target < 0) {
                        pid_temperature.target = 0;
                    }
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_PID_SET_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                case KEY_BACK:
                    pid_temperature.target = float_temp_value;
                    DISABLE_GLOBAL_INTERRUPT();
                    display_clear();
                    PA_PID_SET_MENU();
                    ENABLE_GLOBAL_INTERRUPT();
                    break;
                default:
                    pid_temperature_target_cnt = 0;
                    break;
            }
        }
    }
}

static void Delay10ms(void) //@11.0592MHz
{
    unsigned char i, j;

    i = 18;
    j = 235;
    do {
        while (--j);
    } while (--i);
}