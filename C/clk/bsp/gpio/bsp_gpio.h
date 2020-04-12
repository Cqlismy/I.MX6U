#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "imx6ul.h"

/* GPIO输入方向定义 */
typedef enum _gpio_pin_direction {
    kGPIO_DigitalInput = 0U,    /* 表示GPIO方向输入 */
    kGPIO_DigitalOutput = 1U,   /* 表示GPIO方向输出 */
} gpio_pin_direction_t;

typedef struct _gpio_pin_config {
    gpio_pin_direction_t direction; /* GPIO的方向 */
    unsigned char value;  /* GPIO输出时默认引脚电平值 */
} gpio_pin_config_t;

/* GPIO操作函数相关声名 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config);
int gpio_pin_read(GPIO_Type *base, int gpio);
void gpio_pin_write(GPIO_Type *base, int gpio, int value);

#endif