#include "algorithm.h"

idata PID_t pid_temperature = {0};


void pid_init()
{
    pid_temperature.kp = 0;
    pid_temperature.ki = 0;
    pid_temperature.kd = 0;
}

/* 增量式PID 控制输出增量 */
void pid_calculate(float temperature)
{
    /* 当前误差 */
    pid_temperature.error = pid_temperature.target - temperature;

    pid_temperature.output += 
    pid_temperature.kp * (pid_temperature.error - pid_temperature.error_last) + 
    pid_temperature.ki * pid_temperature.error + 
    pid_temperature.kd * (pid_temperature.error - 2 * pid_temperature.error_last + pid_temperature.error_last_last);
    
    pid_temperature.error_last_last = pid_temperature.error_last;
    pid_temperature.error_last = pid_temperature.error;

    if (pid_temperature.output > PID_LIMIT_MAX)
    {
        pid_temperature.output = PID_LIMIT_MAX;
    }
    if (pid_temperature.output < PID_LIMIT_MIN)
    {
        pid_temperature.output = PID_LIMIT_MIN;
    }
}

void temperature_to_pwm(int16_t *temperature, uint8_t *pwm)
{
    /* 计算当前温度 */
    float temp = *temperature > 0 ? (float)*temperature/16 : -(float)(*temperature&0x7FFF)/16;
    if (temp > T_up)
    {
        *pwm = 100;
    }
    else if (temp < T_down)
    {
        *pwm = 0;
    }
    else
    {
        *pwm = (uint8_t)(((temp - T_down) / (T_up - T_down)) * 50 + 50);
    }
}