# SAT_OS — RP2040 Embedded Firmware Project

## Overview

SAT_OS is a completed RP2040-based embedded firmware project that integrates peripheral drivers, sensor data acquisition, scheduled tasks, telemetry, and SD-card data logging into a single firmware application.

Before developing SAT_OS, I completed a separate RP2040 bare-metal peripheral-learning project in which I explored and implemented fundamental microcontroller peripherals. The practical knowledge gained from that project helped me develop and integrate the firmware modules used in SAT_OS.

I developed the firmware modules myself and worked through the code to understand how the individual components operate and interact. I tested the implemented functionality on hardware before considering the project complete.

This project represents an important step in my embedded systems learning journey. After completing the RP2040 projects, I moved on to STM32 bare-metal development to deepen my understanding of register-level programming, peripheral drivers, interrupts, and microcontroller architecture.

## Hardware

- **Microcontroller:** Raspberry Pi Pico / RP2040
- **BMP280:** Temperature and barometric-pressure measurements
- **MPU6050:** Accelerometer and gyroscope measurements
- **MQ-2:** Gas and smoke sensing
- **SD-card module:** Data storage and logging

## Firmware Features

### Peripheral Drivers

The firmware includes implementations for the following peripherals and interfaces:

- GPIO — General-purpose input/output control
- UART — Serial communication
- I2C — Communication with supported sensors
- SPI — Serial peripheral communication
- ADC — Analog signal acquisition

### Sensor Interfaces

- **BMP280:** Acquires temperature and barometric-pressure data.
- **MPU6050:** Interfaces with the accelerometer and gyroscope to acquire motion-related data.
- **MQ-2:** Interfaces with the gas and smoke sensor module to obtain sensor readings.

### Firmware Architecture

- Modular embedded C source and header files
- Peripheral driver integration
- Scheduled tasks and periodic execution
- Sensor data acquisition
- Telemetry collection and transmission
- SD-card data logging

The project brings these components together into an integrated firmware application rather than treating each peripheral as an isolated experiment.

## Software Structure

```text
SAT_OS/
├── inc/                    # Header files and shared configuration
├── src/                    # Firmware source files
├── docs/                   # Project documentation
├── dashboard/              # PC-side Python dashboard
├── CMakeLists.txt          # CMake build configuration
├── pico_sdk_import.cmake   # Pico SDK integration
├── .gitignore
└── README.md
```

## Development Environment

- **Programming language:** C
- **Microcontroller platform:** Raspberry Pi Pico / RP2040
- **SDK:** Raspberry Pi Pico SDK
- **Build system:** CMake
- **Toolchain:** ARM embedded GCC toolchain
- **PC-side tools:** Python-based serial telemetry dashboard

## Testing and Verification

The implemented firmware functionality was tested on hardware during development. Testing covered the implemented peripheral interfaces, sensor interactions, and integrated project functionality.

The project was completed after implementing and testing the intended firmware features.

## PC Dashboard

The repository includes a PC-side Python dashboard for receiving and displaying serial telemetry.

**The dashboard was not developed by me.** It is included as a supporting component of the repository; my development work focused on the embedded firmware.

The serial port and required Python packages may need to be configured for the local computer before using the dashboard.

## Building the Firmware

The firmware uses the Raspberry Pi Pico SDK and CMake.

General build requirements:

1. Install the Raspberry Pi Pico SDK.
2. Install CMake, Ninja or another supported build tool, and the ARM embedded GCC toolchain.
3. Configure the Pico SDK path for the local environment.
4. Generate the build system using the project's CMake configuration.
5. Compile the firmware and follow the project documentation for flashing it to the board.

Build configuration may require environment-specific adjustments depending on the installed SDK and toolchain versions.

## Learning Outcomes

Through this project, I gained practical experience in:

- Implementing and integrating embedded C peripheral drivers
- Working with GPIO, UART, I2C, SPI, and ADC
- Interfacing with multiple sensors
- Collecting and processing sensor data
- Implementing scheduled tasks and periodic operations
- Handling serial telemetry
- Logging data to an SD card
- Organizing modular firmware source code and header files
- Developing and testing an integrated RP2040 firmware application
- Using the Raspberry Pi Pico SDK and CMake build system

The experience gained from my initial RP2040 peripheral experiments provided the foundation for this project and prepared me for further low-level embedded development.

## Project Status

**Status: Completed and tested**

SAT_OS is a completed embedded firmware project developed on the RP2040 platform. This repository preserves the firmware source code, project structure, and supporting documentation as part of my embedded systems portfolio.

My current learning focus has progressed to STM32 bare-metal development, where I am continuing to explore register-level programming, peripheral drivers, interrupts, and microcontroller architecture.
