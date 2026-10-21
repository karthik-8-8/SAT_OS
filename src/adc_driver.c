#include "adc_driver.h"

#include "hardware/adc.h"
#include  "pico/stdlib.h"

void ADC_Init(void)
{
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
}
void ADC_SelectChannel(uint8_t channel)
{
    adc_select_input(channel);
}

uint16_t ADC_ReadRaw(void)
{
    return adc_read();
}
float ADC_ReadVoltage(void)
{
    uint16_t adc_raw=ADC_ReadRaw();

    float voltage = ((float)adc_raw*ADC_REF_VOLTAGE)/ADC_MAX_VALUE;
    return voltage;
}

