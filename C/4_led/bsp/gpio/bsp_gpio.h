#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "imx6ul.h"

#define hight   1
#define low     0

/* GPIO操作函数声明 */
void gpio_init(void);
void gpio_output(int status);

#endif