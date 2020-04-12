#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6ul.h"
#include "bsp_gpio.h"

#define ON      1
#define OFF     0

void led_init(void);
void led_switch(int status);

#endif