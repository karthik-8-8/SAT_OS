#include "spi_driver.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#define SPI_PORT      spi1

#define SPI_MISO_PIN  12
#define SPI_MOSI_PIN  15
#define SPI_SCK_PIN   14

void SPI_Init(void)
{
    spi_init(SPI_PORT,400000);
    spi_set_format(SPI_PORT,
                   8,
                   SPI_CPOL_0,
                   SPI_CPHA_0,
                   SPI_MSB_FIRST);
    gpio_set_function(SPI_MISO_PIN,GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN,GPIO_FUNC_SPI);
    gpio_set_function(SPI_SCK_PIN,GPIO_FUNC_SPI);
}
void SPI_Write(const uint8_t *tx_buffer, size_t length)
{
    spi_write_blocking(SPI_PORT,tx_buffer,length);
}

void SPI_Read(uint8_t *rx_buffer, size_t length)
{
    spi_read_blocking(SPI_PORT,0xFF,rx_buffer,length);
}

void SPI_Transfer(const uint8_t *tx_buffer,
                  uint8_t *rx_buffer,
                  size_t length)
{
    spi_write_read_blocking(SPI_PORT,
                        tx_buffer,
                        rx_buffer,
                        length);
}
