#ifndef __BSP_EEPROM_H
#define __BSP_EEPROM_H
#include "main.h"

#define EEPROM_ADDR 0xA6
#define EERPOM_SIZE 2048
#define EEPROM_PAGE 16

// 只使用前16页 256字节大小
void eeprom_write_bytes(uint8_t addr, uint8_t *dat, uint8_t len);
void eeprom_read_bytes(uint8_t addr, uint8_t *dat, uint8_t len);

#endif // __BSP_EEPROM_H
