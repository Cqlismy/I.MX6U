#include "bsp_gptint.h"
#include "bsp_int.h"
#include "bsp_led.h"

/**
 * gpt2_init() - GPT2定时器初始化函数
 * 
 * @prescalar: 分频值，能设置的范围为1~4096
 * @value: 装载值 
 * 
 * @return: 无
 */
void gpt2_init(unsigned int prescalar, unsigned int value)
{
    if (prescalar > 4096)
        prescalar = 4096;
    
    GPT2->CR = 0;           /* GPT2_CR寄存器清0 */
    GPT2->CR |= 1 << 15;    /* GPT2定时器进入软复位状态 */
    while ((GPT2->CR >> 15) & 0x01);    /* 等待软复位完成 */

    /**
     * 配置GPT2_CR寄存器相关位
     * bit[22:20]: 000 输出比较功能关闭
     * bit[9]: 0 GPT2定时器工作于Restart模式
     * bit[8:6]: 001 GPT2时钟源选择ipg_clk=66MHz
     */
    GPT2->CR |= (1 << 6);

    /**
     * 配置GPT2_PR寄存器，设置时钟分频系数
     * bit[11:0]: 分频值，0x000~0xFFF代表1~4096分频
     */
    GPT2->PR = prescalar - 1;

    /**
     * 配置GPT2_OCR1寄存器，输出比较1的计数值
     */
    GPT2->OCR[0] = value;

    /**
     * 配置GPT2_IR寄存器，使能输出比较1中断
     * bit[0]: 1 输出比较1中断使能
     */
    GPT2->IR |= 1 << 0;

    GIC_EnableIRQ(GPT2_IRQn);    /* 使能GIC相应的GPT2中断 */

    /* 注册GPT2的中断服务函数 */
    system_register_irqhandler(GPT2_IRQn,
        (system_irq_handler_t)gpt2_irqhandler, NULL);

    GPT2->CR |= 1 << 0; /* 使能GPT2定时器 */
}

/**
 * gpt2_irqhandler() - GPT2中断服务处理函数
 * 
 * @giccIar: 中断号
 * @userParam: 用户参数 
 * 
 * @return: 无
 */
void gpt2_irqhandler(unsigned int giccIar, void *userParam)
{
    static unsigned char led1_state;

    led1_state = !led1_state;
    if (GPT2->SR & (1 << 0))
        led_switch(LED1, led1_state);

    GPT2->SR |= 1 << 0; /* 清除GPT2输出比较1中断标志位 */
}