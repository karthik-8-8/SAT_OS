#include "gpio.h"

#include "pico/stdlib.h"

void GPIO_Init(void)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);   
}

void LED_On(void)
{
    gpio_put(LED_PIN,1);
}

void LED_Off(void)
{
    gpio_put(LED_PIN,0);
}

void LED_Toggle(void)
{
    gpio_xor_mask(1u<<LED_PIN);
}