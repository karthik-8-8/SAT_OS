#ifndef TASK_H
#define TASK_H

#include "scheduler.h"
extern Task_t heartbeat;
extern Task_t telemetry;
extern Task_t bmp280;
extern Task_t mpu6050;
extern Task_t mq2;
extern Task_t sdcard;



void Heartbeat_Task(void);
void Telemetry_Task(void);
void BMP280_Task(void);
void MPU6050_Task(void);
void MQ2_Task(void);


#endif