#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__
#include "main.h"

typedef struct
{
    float kp;
    float ki;
    float kd;
    float error;
    float error_last;
    float error_sum;
    float target;
    float output;
}PID_t;


#endif // __ALGORITHM_H
