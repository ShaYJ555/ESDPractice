#ifndef __BSP_SENSOR_H
#define __BSP_SENSOR_H
#include "main.h"

void ds18b20_init(void);
void ds18b20_read_temperature(uint16_t *dat);

#endif // __BSP_SENSOR_H
