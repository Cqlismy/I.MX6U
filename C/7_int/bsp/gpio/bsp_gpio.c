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

    gpio_interrupt_config(base, pin, config->interruptmode); /* GPIO中断配置 */
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

/**
 * gpio_interrupt_config() - 设置GPIO中断触发配置
 * 
 * @base: 要设置的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要设置的GPIO组的pin编号
 * @interruptmode: 要设置的GPIO中断触发方式
 * 
 * @return: 无
 */
void gpio_interrupt_config(GPIO_Type *base, int pin,
        gpio_interrupt_mode_t interruptmode)
{
    volatile unsigned int *icr;
    unsigned int icrshift = pin;

    base->EDGE_SEL &= ~(1 << pin);  /* 双边沿触发寄存器清0 */
    base->IMR &= ~(1 << pin);   /* 禁止GPIO中断 */

    if (pin < 16) {
        icr = &(base->ICR1);    /* GPIOx_IO00~GPIOx_IO15 */
    } else {
        icr = &(base->ICR2);    /* GPIOx_IO16~GPIOx_IO31 */
        icrshift -= 16;
    }

    *icr &= ~(3 << (2 * icrshift));
    switch (interruptmode) {
    case (kGPIO_IntLowLevel):
        *icr |= (0 << (2 * icrshift));
        break;
    case (kGPIO_IntHighLevel):
        *icr |= (1 << (2 * icrshift));
        break;
    case (kGPIO_IntRisingEdge):
        *icr |= (2 << (2 * icrshift));
        break;
    case (kGPIO_IntFallingEdge):
        *icr |= (3 << (2 * icrshift));
        break;
    case (kGPIO_IntRisingOrFallingEdge):
        base->EDGE_SEL |= (1 << pin);
        break;
    default:
        break;
    }
}

/**
 * gpio_enable_interrupt() - 使能GPIO引脚中断
 * 
 * @base: 要设置的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要设置的GPIO组的pin编号
 * 
 * @return: 无
 */
void gpio_enable_interrupt(GPIO_Type *base, int pin)
{
    base->IMR |= (1 << pin);
}

/**
 * gpio_disable_interrupt() - 禁止GPIO引脚中断
 * 
 * @base: 要设置的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要设置的GPIO组的pin编号
 * 
 * @return: 无
 */
void gpio_disable_interrupt(GPIO_Type *base, int pin)
{
    base->IMR &= ~(1 << pin);
}

/**
 * gpio_clear_int_flags() - 清除GPIO中断标志位
 * 
 * @base: 要设置的GPIO组，例如：GPIO1、GPIO2
 * @pin: 要设置的GPIO组的pin编号
 * 
 * @return: 无
 */
void gpio_clear_int_flags(GPIO_Type *base, int pin)
{
    base->ISR |= (1 << pin);    /* 写1清除中断标志位 */
}