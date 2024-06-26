#include "algorithm.h"

idata PID_t pid_temperature = {0};


void pid_init()
{
    pid_temperature.target = 0;
    pid_temperature.kp = 0.01;
    pid_temperature.ki = 0.01;
    pid_temperature.kd = 0.01;
}

void pid_calculate(float temperature)
{
    /* µ±Ç°Îó²î */
    pid_temperature.error = pid_temperature.target - temperature;

    pid_temperature.error_sum += pid_temperature.error * pid_temperature.ki;
    pid_temperature.error_last = pid_temperature.error;
    
    pid_temperature.output = pid_temperature.kp * pid_temperature.error +
                             pid_temperature.ki * (pid_temperature.error - pid_temperature.error_last) + 
                             pid_temperature.kd * (pid_temperature.error - pid_temperature.error_last);
    
    pid_temperature.error_last = pid_temperature.error;
    
    if (pid_temperature.output > 100)
    {
        pid_temperature.output = 100;
    }
    if (pid_temperature.output < 0)
    {
        pid_temperature.output = 0;
    }
}