#ifndef __BSP_EEPROM_H
#define __BSP_EEPROM_H
#include "main.h"

#define EEPROM_ADDR 0xA0
#define EERPOM_SIZE 2048
#define EEPROM_PAGE 16

void eeprom_write_bytes(uint8_t addr, uint8_t *dat, uint8_t len);
void eeprom_read_bytes(uint8_t addr, uint8_t *dat, uint8_t len);

#endif // __BSP_EEPROM_H
