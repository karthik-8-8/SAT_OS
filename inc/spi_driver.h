#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "sat_os.h"

void SPI_Init(void);

void SPI_Write(const uint8_t *tx_buffer, size_t length);

void SPI_Read(uint8_t *rx_buffer, size_t length);

void SPI_Transfer(const uint8_t *tx_buffer,
                  uint8_t *rx_buffer,
                  size_t length);

#endif