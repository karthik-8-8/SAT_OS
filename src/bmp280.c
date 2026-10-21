#include "bmp280.h"
#include  "i2c_driver.h"
#include  <stdio.h>
#include  "pico/stdlib.h"
#include  "math.h"

static BMP280_Calib_t calib;
static int32_t t_fine;

static bool BMP280_ReadCalibration(void)
{
    uint8_t buffer[24];

    if(!I2C_ReadRegisters(0x76, 0x88, buffer, 24))
    {
        return false;
    }

    calib.dig_T1 = (buffer[1]  << 8) | buffer[0];
    calib.dig_T2 = (buffer[3]  << 8) | buffer[2];
    calib.dig_T3 = (buffer[5]  << 8) | buffer[4];

    calib.dig_P1 = (buffer[7]  << 8) | buffer[6];
    calib.dig_P2 = (buffer[9]  << 8) | buffer[8];
    calib.dig_P3 = (buffer[11] << 8) | buffer[10];
    calib.dig_P4 = (buffer[13] << 8) | buffer[12];
    calib.dig_P5 = (buffer[15] << 8) | buffer[14];
    calib.dig_P6 = (buffer[17] << 8) | buffer[16];
    calib.dig_P7 = (buffer[19] << 8) | buffer[18];
    calib.dig_P8 = (buffer[21] << 8) | buffer[20];
    calib.dig_P9 = (buffer[23] << 8) | buffer[22];

    bool ok1 = I2C_WriteRegister(0x76, 0xF5, 0x00);
    bool ok2 = I2C_WriteRegister(0x76, 0xF4, 0x27);

    
    return true;
}


static bool BMP280_ReadRawData(int32_t *raw_temp,
                               int32_t *raw_press)
{
    uint8_t buffer[6];

    if(!I2C_ReadRegisters(0x76, 0xF7, buffer, 6))
    {
        return false;
    }
   

    *raw_press =
        ((int32_t)buffer[0] << 12) |
        ((int32_t)buffer[1] << 4)  |
        (buffer[2] >> 4);

    *raw_temp =
        ((int32_t)buffer[3] << 12) |
        ((int32_t)buffer[4] << 4)  |
        (buffer[5] >> 4);


    return true;
}
bool BMP280_ReadData(BMP280_Data_t *data)
{
    int32_t raw_temp;
    int32_t raw_press;


    if(!BMP280_ReadRawData(&raw_temp, &raw_press))
    {
        return false;
    }

    int32_t var1;
    int32_t var2;

    var1 = ((((raw_temp >> 3) -
            ((int32_t)calib.dig_T1 << 1))) *
            ((int32_t)calib.dig_T2)) >> 11;

    var2 = (((((raw_temp >> 4) -
            ((int32_t)calib.dig_T1)) *
            ((raw_temp >> 4) -
            ((int32_t)calib.dig_T1))) >> 12) *
            ((int32_t)calib.dig_T3)) >> 14;

    t_fine = var1 + var2;
    int64_t var1_p;
    int64_t var2_p;
    int64_t p;

    var1_p = ((int64_t)t_fine) - 128000;

    var2_p = var1_p * var1_p * (int64_t)calib.dig_P6;
    var2_p = var2_p + ((var1_p * (int64_t)calib.dig_P5) << 17);
    var2_p = var2_p + (((int64_t)calib.dig_P4) << 35);

    var1_p =
        ((var1_p * var1_p * (int64_t)calib.dig_P3) >> 8) +
        ((var1_p * (int64_t)calib.dig_P2) << 12);

    var1_p =
        (((((int64_t)1) << 47) + var1_p) *
        ((int64_t)calib.dig_P1)) >> 33;

    if (var1_p == 0)
    {
        return false;
    }

    p = 1048576 - raw_press;

    p = (((p << 31) - var2_p) * 3125) / var1_p;

    var1_p = (((int64_t)calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;

    var2_p = (((int64_t)calib.dig_P8) * p) >> 19;

    p = ((p + var1_p + var2_p) >> 8) +
        (((int64_t)calib.dig_P7) << 4);

    float temperature = (t_fine * 5 + 128) >> 8;
    data->temperature = temperature / 100.0f;
    data->pressure = (float)p / 256.0f / 100.0f;
    data->altitude = 44330.0f *
           (1.0f - powf(data->pressure/ 1013.25f, 0.1903f));

    return true;
}



void BMP280_Init(void)
{
    uint8_t id;

    if(I2C_ReadRegister(0x76,0xD0,&id))
    {
        printf("BMP280 ID=0x%2X\r\n",id);

        BMP280_ReadCalibration();
        uint8_t ctrl;

if (I2C_ReadRegister(0x76, 0xF4, &ctrl))
{
    printf("CTRL after init = 0x%02X\r\n", ctrl);
}

    }
    else
    {
        printf("BMP280 not detected\r\n");
    }
}
