#include "i2c_driver.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define I2C_PORT i2c0

#define SDA_PIN 0
#define SCL_PIN 1

void I2C_Driver_Init(void)
{
    i2c_init(I2C_PORT,400000);

    gpio_set_function(SDA_PIN,GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN,GPIO_FUNC_I2C);
    
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

bool I2C_ReadRegister(uint8_t dev_addr,
                      uint8_t reg_addr,
                      uint8_t *data)

{
    int ret;

    ret=i2c_write_blocking(I2C_PORT,dev_addr,&reg_addr,1,true);

    if(ret<0)
        return false;

    ret=i2c_read_blocking(I2C_PORT,dev_addr,data,1,false);

    if(ret<0)
        return false;
    
    return true;

}
bool I2C_ReadRegisters(uint8_t dev_addr,
                       uint8_t reg_addr,
                       uint8_t *buffer,
                       uint8_t length)
{
    if(i2c_write_blocking(I2C_PORT,
                          dev_addr,
                          &reg_addr,
                          1,
                          true) < 0)
    {
        return false;
    }

    if(i2c_read_blocking(I2C_PORT,
                         dev_addr,
                         buffer,
                         length,
                         false) < 0)
    {
        return false;
    }

    return true;
}

bool I2C_WriteRegister(uint8_t dev_addr,
                       uint8_t reg_addr,
                       uint8_t value)
{
    uint8_t buffer[2];

    buffer[0]=reg_addr;
    buffer[1]=value;

    if(i2c_write_blocking(I2C_PORT,dev_addr,buffer,2,false)<0)
    {
        return false;
    }

    return true;

}