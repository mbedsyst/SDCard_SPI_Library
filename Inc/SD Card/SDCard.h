#ifndef __SDCARD_H__
#define __SDCARD_H__

#include "Drivers/SPI.h"
  
void SD_Reset(void);
void SD_WriteBlock(uint32_t address, uint8_t *data, uint16_t size);
void SD_ReadBlock(uint32_t address, uint8_t *data, uint16_t size);

#endif
