#include "gpio.h"
#include "uart.h"
#include "scheduler.h"
#include "pico/stdlib.h"
#include "task.h"
#include "i2c_driver.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "mq2.h"
#include "spi_driver.h"
#include "sdcard.h"
#include  "telemetry_logger.h"

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    GPIO_Init();
    UART_Init();
    I2C_Driver_Init();
    ADC_Init();
    SPI_Init();
    
    BMP280_Init();
    mpu6050_init();
    MQ2_Init();
    TelemetryLogger_Init();
    
    if (SD_Init())
        {
            printf("SD Card Initialized\r\n");
        }
    else
        {
            printf("SD Card Initialization Failed\r\n");
        }
      
    Scheduler_Init();

    Scheduler_Addtask(&heartbeat);
    Scheduler_Addtask(&bmp280);
    Scheduler_Addtask(&mpu6050);
    Scheduler_Addtask(&mq2);
    Scheduler_Addtask(&sdcard);
    Scheduler_Addtask(&telemetry);
    
    while(1)
    {
       Scheduler_Run(); 
    }
}