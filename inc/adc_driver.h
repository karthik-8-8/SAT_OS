#ifndef ADC_H
#define ADC_H

#include "sat_os.h"

#define ADC_REF_VOLTAGE 3.3f
#define ADC_MAX_VALUE   4095U



void ADC_Init(void);

void ADC_SelectChannel(uint8_t channel);

uint16_t ADC_ReadRaw(void);

float ADC_ReadVoltage(void);


#endif