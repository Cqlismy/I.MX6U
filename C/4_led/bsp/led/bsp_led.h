#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6ul.h"

#define LED_ON   1
#define LED_OFF  0

/* GPIO操作函数声明 */
void led_init(void);
void led_output(int status);

#endif