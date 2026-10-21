#ifndef MQ2_H
#define MQ2_H

#include "adc_driver.h"


typedef struct 
{
   const  char *quality;
} MQ2_Data_t;

void MQ2_Init(void);
void MQ2_ReadData(void);

extern MQ2_Data_t mq2_data;

#endif