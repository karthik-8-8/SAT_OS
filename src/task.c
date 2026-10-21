#include "task.h"
#include  "gpio.h"
#include  "uart.h"
#include  "bmp280.h"
#include  "mpu6050.h"
#include  "mq2.h"
#include  "sdcard.h"
#include "telemetry.h"
#include "telemetry_logger.h"
#include <string.h>

void Heartbeat_Task(void)
{
    LED_Toggle();
}



BMP280_Data_t bmp_data;

void BMP280_Task(void)
{
    if(BMP280_ReadData(&bmp_data))
    {
    }
}

MPU6050_Data_t mpu6050_data;
void MPU6050_Task(void)
{
    if(MPU6050_ReadData(&mpu6050_data))
    {
    }

}

void MQ2_Task(void)
{
    MQ2_ReadData();
}

void SD_Task(void)
{
    Telemetry_Record_t record;

    Telemetry_CreateRecord(&record);

    if(!TelemetryLogger_AddRecord(&record))
    {
        printf("Logger Error\r\n");
    }
    
    
}


void Telemetry_Task(void)
{
    
    static char buffer[512];

    snprintf(buffer, sizeof(buffer),
    "%.2f,%.2f,%.2f,"
    "%.3f,%.3f,%.3f,"
    "%.3f,%.3f,%.3f,"
    "%s\r\n",

    bmp_data.temperature,
    bmp_data.pressure,
    bmp_data.altitude,

    mpu6050_data.ax,
    mpu6050_data.ay,
    mpu6050_data.az,

    mpu6050_data.gx,
    mpu6050_data.gy,
    mpu6050_data.gz,

    mq2_data.quality
);

UART_SendString(buffer);
    //UART_SendString(buffer);
}

Task_t heartbeat =
{
    .task = Heartbeat_Task,
    .period_ms = 500,
    .last_run = 0
};

Task_t telemetry =
{
    .task = Telemetry_Task,
    .period_ms = 1000,
    .last_run = 0
};

Task_t bmp280=
{
    .task = BMP280_Task,
    .period_ms = 100,
    .last_run =0
};

Task_t mpu6050=
{
    .task=MPU6050_Task,
    .period_ms=100,
    .last_run=0
};

Task_t mq2=
{
    .task=MQ2_Task,
    .period_ms=100,
    .last_run=0
};

Task_t sdcard=
{
    .task=SD_Task,
    .period_ms=1000,
    .last_run=0
};