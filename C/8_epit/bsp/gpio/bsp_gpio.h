#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "imx6ul.h"

/* GPIO输入方向定义 */
typedef enum _gpio_pin_direction {
    kGPIO_DigitalInput = 0U,    /* 表示GPIO方向输入 */
    kGPIO_DigitalOutput = 1U,   /* 表示GPIO方向输出 */
} gpio_pin_direction_t;

/* 枚举GPIO外部中断触发类型 */
typedef enum _gpio_interrupt_mode {
    kGPIO_NoIntmode = 0U,               /* 无中断触发功能 */
    kGPIO_IntLowLevel = 1U,             /* 低电平触发 */
    kGPIO_IntHighLevel = 2U,            /* 高电平触发 */
    kGPIO_IntRisingEdge = 3U,           /* 上升沿触发 */
    kGPIO_IntFallingEdge = 4U,          /* 下降沿触发 */
    kGPIO_IntRisingOrFallingEdge = 5U,  /* 双边沿触发 */
} gpio_interrupt_mode_t;

/* GPIO引脚配置结构体 */
typedef struct _gpio_pin_config {
    gpio_pin_direction_t direction;         /* GPIO的方向 */
    unsigned char value;                    /* GPIO输出时默认引脚电平值 */
    gpio_interrupt_mode_t interruptmode;    /* 中断触发方式 */
} gpio_pin_config_t;

/* GPIO操作函数相关声名 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config);
int gpio_pin_read(GPIO_Type *base, int pin);
void gpio_pin_write(GPIO_Type *base, int pin, int value);

/* GPIO中断相关操作函数声明 */
void gpio_interrupt_config(GPIO_Type *base, int pin,
        gpio_interrupt_mode_t interruptmode);
void gpio_enable_interrupt(GPIO_Type *base, int pin);
void gpio_disable_interrupt(GPIO_Type *base, int pin);
void gpio_clear_int_flags(GPIO_Type *base, int pin);

#endif