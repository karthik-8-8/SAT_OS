#include "mq2.h"


MQ2_Data_t mq2_data;

void MQ2_Init(void)
{
    
}

void MQ2_ReadData(void)
{
     ADC_SelectChannel(0);

    float voltage = ADC_ReadVoltage();

    if (voltage < 1.20f)
    {
        mq2_data.quality="CLEAN";
    }
    else if (voltage < 1.80f)
    {
        mq2_data.quality="MODERATE";
    }
    else if (voltage < 2.50f)
    {
        mq2_data.quality="POOR";
    }
    else
    {
        mq2_data.quality="HAZARDOUS";
    }
}