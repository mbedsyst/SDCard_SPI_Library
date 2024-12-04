#ifndef __SDCARD_H__
#define __SDCARD_H__

#include "Drivers/SPI.h"


uint8_t SD_Reset(void);
uint8_t SD_WriteBlock(uint32_t blockAddr, uint8_t *data);

#endif
