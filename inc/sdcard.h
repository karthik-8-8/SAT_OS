#ifndef SDCARD_H
#define SDCARD_H

#include "sat_os.h"
#include "spi_driver.h"


bool SD_Init(void);

bool SD_ReadBlock(uint32_t block_address,uint8_t *buffer);

bool SD_WriteBlock(uint32_t block_address,const uint8_t *buffer);


#endif