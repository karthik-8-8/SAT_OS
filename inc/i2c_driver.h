#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "sat_os.h"

void I2C_Driver_Init(void);


bool I2C_WriteRegister(uint8_t dev_addr,
                       uint8_t reg_addr,
                       uint8_t data);

bool I2C_ReadRegister(uint8_t dev_addr,
                      uint8_t reg_addr,
                      uint8_t *data);

bool I2C_ReadRegisters(uint8_t dev_addr,
                       uint8_t reg_addr,
                       uint8_t *buffer,
                       uint8_t length);




#endif