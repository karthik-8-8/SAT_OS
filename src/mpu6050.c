#include "mpu6050.h"
#include "i2c_driver.h"
#include "pico/stdlib.h"

bool mpu6050_read_accel_raw(int16_t *ax,
                            int16_t *ay,
                            int16_t *az,
                            int16_t *temp,
                            int16_t *gx,
                            int16_t *gy,
                            int16_t *gz
                            )
{
    uint8_t buffer[14];
    if(!I2C_ReadRegisters(MPU6050_ADDR,0x3B,buffer,14))
    {
        return false;
    }

        *ax=(int16_t)(buffer[0]<<8)|buffer[1];
        *ay=(int16_t)(buffer[2]<<8)|buffer[3];
        *az=(int16_t)(buffer[4]<<8)|buffer[5];
        *temp=((int16_t)(buffer[6] << 8) | buffer[7]);
        *gx=(int16_t)(buffer[8] << 8) | buffer[9];
        *gy=(int16_t)(buffer[10] << 8) | buffer[11];
        *gz=(int16_t)(buffer[12] << 8) | buffer[13];
        
        return true;
    
}
bool MPU6050_ReadData(MPU6050_Data_t *mpudata)
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t temp;
    int16_t gx;
    int16_t gy;
    int16_t gz;

    if(!mpu6050_read_accel_raw(&ax,&ay,&az,&temp,&gx,&gy,&gz))
    {
        return false;
    }
    mpudata->ax = ax / 16384.0f;
    mpudata->ay = ay / 16384.0f;
    mpudata->az = az / 16384.0f;
    mpudata->temp =
        (temp / 340.0f) + 36.53f;
    mpudata->gx = gx / 131.0f;
    mpudata->gy = gy / 131.0f;
    mpudata->gz = gz / 131.0f;

    return true;
    
}
bool mpu6050_init(void)
{
    uint8_t id;

    if(!I2C_ReadRegister(MPU6050_ADDR,MPU6050_WHO_AM_I,&id))
    {
        return false;
    }

    if(id!=0x68)
    {
        return false;
    }

    if(!I2C_WriteRegister(MPU6050_ADDR,MPU6050_PWR_MGMT_1,0x00))
    {
        return false;
    }
    return true;
    
}