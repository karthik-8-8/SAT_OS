#ifndef MPU6050_H
#define MPU6050_H

#include "sat_os.h"

#define MPU6050_ADDR    0x68

/* Registers */
#define MPU6050_WHO_AM_I       0x75
#define MPU6050_PWR_MGMT_1     0x6B

typedef struct
{
    float ax;
    float ay;
    float az;

    float temp;

    float gx;
    float gy;
    float gz;

      
} MPU6050_Data_t;


bool mpu6050_init(void);
bool mpu6050_read_accel_raw(int16_t *ax,
                            int16_t *ay,
                            int16_t *az,
                            int16_t *temp,
                            int16_t *gx,
                            int16_t *gy,
                            int16_t *gz
                        );

bool MPU6050_ReadData(MPU6050_Data_t *mpudata);
#endif