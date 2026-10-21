#ifndef BMP280_H
#define BMP280_H

#include "sat_os.h"

typedef struct
{
    float temperature;
    float pressure;
    float altitude;
} BMP280_Data_t;

typedef struct
{
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;

    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

} BMP280_Calib_t;

void BMP280_Init(void);

bool BMP280_ReadData(BMP280_Data_t *data);


#endif