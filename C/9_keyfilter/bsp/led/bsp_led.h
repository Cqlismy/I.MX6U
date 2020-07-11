#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6ul.h"
#include "bsp_gpio.h"

/* LED灯号 */
#define LED1    0   /* 系统运行提示LED */
#define LED2    1

/* LED灯的开关状态 */
#define OFF      0
#define ON       1

void led_init(void);
void led_switch(unsigned char led, unsigned char status);

#endif