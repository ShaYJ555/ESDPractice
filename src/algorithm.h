#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__
#include "main.h"

typedef struct
{
    int16_t kp;
    int16_t ki;
    int16_t kd;
    int16_t error;
    int16_t error_last;
    int16_t error_last_last;
    int16_t error_sum;
    int16_t target;
    int16_t output;
}PID_t;

#define PID_LIMIT_MIN    0
#define PID_LIMIT_MAX    100

void temperature_to_pwm(uint16_t temperature, uint8_t *pwm);

#endif // __ALGORITHM_H
