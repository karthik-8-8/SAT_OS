cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(SAT_OS C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(SAT_OS

    src/main.c
    src/gpio.c
    src/uart.c
    src/scheduler.c
    src/task.c
    src/bmp280.c
    src/i2c_driver.c
    src/mpu6050.c
    src/adc_driver.c
    src/mq2.c
    src/spi_driver.c
    src/sdcard.c
    src/telemetry.c
    src/telemetry_logger.c
    
)

target_include_directories(SAT_OS PRIVATE

    inc

)

target_link_libraries(SAT_OS

    pico_stdlib
    hardware_i2c
    hardware_adc
    hardware_spi
    hardware_gpio
)

pico_enable_stdio_usb(SAT_OS 1)
pico_enable_stdio_uart(SAT_OS 0)

pico_add_extra_outputs(SAT_OS)

