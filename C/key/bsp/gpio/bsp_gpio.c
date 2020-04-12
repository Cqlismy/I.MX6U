#include "bsp_gpio.h"

/**
 * gpio_init() - GPIO初始化函数
 * 
 * @base: 要初始化的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要初始化的GPIO组的pin编号
 * @config: gpio引脚配置结构体
 * 
 * @return: 无
 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config)
{
    if (config->direction == kGPIO_DigitalInput) /* GPIO方向为输入 */
        base->GDIR &= ~(1 << pin);
    else {
        base->GDIR |= (1 << pin);
        gpio_pin_write(base, pin, config->value);
    }
}

/**
 * gpio_pin_read() - 读取GPIO引脚的电平
 * 
 * @base: 要读取的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要读取的GPIO组的pin编号
 * 
 * @return: 0表示低电平，1表示高电平
 */
int gpio_pin_read(GPIO_Type *base, int pin)
{
    return (((base->DR) >> pin) & 0x1);
}

/**
 * gpio_pin_write() - 设置GPIO引脚的电平
 * 
 * @base: 要设置的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要设置的GPIO组的pin编号
 * @value: 引脚要设置的电平值：0->低电平，1->高电平
 * 
 * @return: 无
 */
void gpio_pin_write(GPIO_Type *base, int pin, int value)
{
    if (0 == value)
        base->DR &= ~(1 << pin); /* 引脚输出低电平 */
    else
        base->DR |= (1 << pin); /* 引脚输出高电平 */
}