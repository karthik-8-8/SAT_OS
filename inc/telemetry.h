#ifndef TELEMETRY_H
#define TELEMETRY_H
#include <stdint.h>




typedef struct 
{
    uint32_t timestamp_ms;

    float bmp_temp;
    float pressure;
    float altitude;

    float ax;
    float ay;
    float az;

    float gx;
    float gy;
    float gz;

    float imu_temp;

    char air_quality[16];
}Telemetry_Record_t;


void Telemetry_CreateRecord(Telemetry_Record_t *record);


#endif