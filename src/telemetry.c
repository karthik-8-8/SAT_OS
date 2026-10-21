#include "telemetry.h"
#include "mq2.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "string.h"
#include "pico/stdlib.h"

extern BMP280_Data_t bmp_data;
extern MPU6050_Data_t mpu6050_data;
extern MQ2_Data_t mq2_data;

void Telemetry_CreateRecord(Telemetry_Record_t *record)
{
    record->timestamp_ms=to_ms_since_boot(get_absolute_time());
    record->bmp_temp=(bmp_data).temperature;
    record->pressure=bmp_data.pressure;
    record->altitude=bmp_data.altitude;

    record->ax=mpu6050_data.ax;
    record->ay=mpu6050_data.ay;
    record->az=mpu6050_data.az;
    
    record->gx=mpu6050_data.gx;
    record->gy=mpu6050_data.gy;
    record->gz=mpu6050_data.gz;

    record->imu_temp=mpu6050_data.temp;

    strcpy(record->air_quality, mq2_data.quality);

}