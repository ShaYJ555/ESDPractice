#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__
#include "main.h"

typedef struct
{
    float kp;
    float ki;
    float kd;
    int16_t error;
    int16_t error_last;
    int16_t error_last_last;
    int16_t error_sum;
    float target;
    int16_t output;
} PID_t;

#define PID_LIMIT_MIN 0
#define PID_LIMIT_MAX 100

void temperature_to_pwm(uint16_t temperature, uint8_t *pwm);
void pid_calculate(uint16_t temperature, PID_t *pid_temperature);
void pid_init(PID_t *pid_temperature);
#endif // __ALGORITHM_H
