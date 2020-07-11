#include "bsp_keyfilter.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_led.h"

/**
 * keyfilter_init() - 按键消抖功能初始化
 * 
 * @param: 无
 * @return: 无
 */
void keyfilter_init(void)
{
    /* 1、按键IO口初始化以及外部中断初始化 */
    gpio_pin_config_t keyfilter_config;

    /* 设置CSI_DATA02引脚IO口复用为GPIO4_IO23 */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA02_GPIO4_IO23, 0);

    /**
     * 配置GPIO4_IO23引脚电气属性
     * bit[16]: 0 关闭HYS
     * bit[15:14]: 11 pull up 22k
     * bit[13]: 1 pull
     * bit[12]: 1 pull/keeper使能
     * bit[11]: 0 禁止开路输出
     * bit[10:8]: 000 resered
     * bit[7:6]: 10 速度为100MHz
     * bit[5:3]: 000 关闭输出
     * bit[2:1]: 00 resered
     * bit[0]: 0 低摆率
     */
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA02_GPIO4_IO23, 0xF080);

    /* 将按键相关的GPIO方向设置为输入，并配置中断 */
    keyfilter_config.direction = kGPIO_DigitalInput;
    keyfilter_config.interruptmode = kGPIO_IntFallingEdge;
    keyfilter_config.value = 1;
    gpio_init(GPIO4, 23, &keyfilter_config);

    /* 使能GIC中断控制器，注册GPIO中断服务函数并使能中断 */
    GIC_EnableIRQ(GPIO4_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO4_Combined_16_31_IRQn,
        (system_irq_handler_t)keyfiltergpio_irqhander, NULL);
    gpio_enable_interrupt(GPIO4, 23);

    /* 2、按键定时器(EPIT2)消抖初始化 */
    keyfiltertimer_init(66, 1000000 / 100); /* 定时10ms */
}

/**
 * keyfiltertimer_init() - 按键消抖EPIT2定时器初始化函数
 * 
 * @prescalar: 分频值，能设置的范围为1~4096
 * @value: 装载值 
 * 
 * @return: 无
 */
void keyfiltertimer_init(unsigned int prescalar, unsigned int value)
{
    if (prescalar > 4096)
        prescalar = 4096;
    
    EPIT2->CR = 0;  /* 将CR寄存器清0 */

    /**
     * 配置EPIT2的CR控制寄存器 
     * bit [25:24]: 01 EPIT2时钟选择Peripheral Clock=66MHz
     * bit [15:4]: prescalar-1 分频器值
     * bit [3]: 1 计数器向下计数到0后从LR重新加载计数器
     * bit [2]: 1 比较中断使能
     * bit [1]: 1 初始计数值来于LR寄存器值 
     * bit [0]: 0 先关闭EPIT2定时器
     */
    EPIT2->CR = (1 << 24 | (prescalar - 1) << 4 | 0xe << 0);
    EPIT2->LR = value;  /* 定时器加载寄存器 */
    EPIT2->CMPR = 0;    /* 定时器比较寄存器 */

    GIC_EnableIRQ(EPIT2_IRQn);  /* 使能GIC相应的EPIT2中断 */

    /* 注册EPIT2的中断服务函数 */
    system_register_irqhandler(EPIT2_IRQn,
        (system_irq_handler_t)keyfiltertimer_irqhandler, NULL);
}

/**
 * keyfiltergpio_irqhander() - 按键GPIO4_IO23中断服务处理函数
 * 
 * @giccIar: 中断号
 * @userParam: 用户参数
 * 
 * @return: 无
 */
void keyfiltergpio_irqhander(unsigned int giccIar, void *userParam)
{
    keyfiltertimer_start(1000000 / 100); /* 开启定时器(定时10ms) */
    gpio_clear_int_flags(GPIO4, 23); /* 清除GPIO4_IO23中断标志位 */
}

/**
 * keyfiltertimer_irqhandler() - 按键消抖定时器(EPIT2)中断服务处理函数
 * 
 * @giccIar: 中断号
 * @userParam: 用户参数 
 * 
 * @return: 无
 */
void keyfiltertimer_irqhandler(unsigned int giccIar, void *userParam)
{
    static unsigned char led_state = OFF;

    if (EPIT2->SR & (1 << 0)) { /* 判断比较中断事件是否产生 */
        keyfiltertimer_stop();
        if (gpio_pin_read(GPIO4, 23) == 0) {
            led_state = !led_state;
            led_switch(LED2, led_state);
        }
    }

    EPIT2->SR |= (1 << 0);  /* 清除定时器中断标志位 */
}

/**
 * keyfiltertimer_start() - 按键消抖定时器(EPIT2)启动
 * 
 * @value: EPIT2定时器装载值
 * 
 * @return: 无
 */
void keyfiltertimer_start(unsigned int value)
{
    EPIT2->CR &= ~(1 << 0);
    EPIT2->LR = value;
    EPIT2->CR |= (1 << 0);
}

/**
 * keyfiltertimer_stop() - 按键消抖定时器(EPIT2)停止
 * 
 * @value: EPIT2定时器装载值
 * 
 * @return: 无
 */
void keyfiltertimer_stop(void)
{
    EPIT2->CR &= ~(1 << 0);
}
