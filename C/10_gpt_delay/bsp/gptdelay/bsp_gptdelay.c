#include "bsp_gptdelay.h"

/**
 * delay_init() - 延时初始化函数(GPT1定时器)
 * 
 * @param: 无
 * @return: 无
 */
void delay_init(void)
{
    GPT1->CR = 0;           /* GPT1_CR寄存器清0 */
    GPT1->CR |= 1 << 15;    /* GPT1定时器进入软复位状态 */
    while ((GPT1->CR >> 15) & 0x01);    /* 等待软复位完成 */

    /**
     * 配置GPT1_CR寄存器相关位
     * bit[22:20]: 000 输出比较功能关闭
     * bit[9]: 0 GPT1定时器工作于Restart模式
     * bit[8:6]: 001 GPT1时钟源选择ipg_clk=66MHz
     */
    GPT1->CR |= (1 << 6);

    /**
     * 配置GPT1_PR寄存器，设置时钟分频系数
     * bit[11:0]: 分频值，0x000~0xFFF代表1~4096分频
     */
    GPT1->PR = 65;      /* GPT1时钟频率为66M/(65+1)=1MHz */

    /**
     * 配置GPT1_OCR1寄存器，输出比较1的计数值
     */
    GPT1->OCR[0] = 0xFFFFFFFF;

    GPT1->CR |= (1 << 0);   /* 使能GPT1定时器开始计数 */
}

/**
 * delay_us() - us级别的延时函数
 * 
 * @us: 要延时的us数，最大延时为0xFFFFFFFFus
 * @return: 无
 */
void delay_us(unsigned int us)
{
    unsigned int oldcnt = 0;
    unsigned int newcnt = 0;
    unsigned int tcntvalue = 0; /* 过去的总时间 */

    oldcnt = GPT1->CNT;
    while (1) {
        newcnt = GPT1->CNT;

        if (newcnt != oldcnt) {
            if (newcnt > oldcnt)    /* 向上计数(计数值没有溢出) */
                tcntvalue = tcntvalue + newcnt - oldcnt;
            else                    /* 计数值发生溢出 */
                tcntvalue = tcntvalue + 0xFFFFFFFF - oldcnt + newcnt;

            oldcnt = newcnt;

            if (tcntvalue >= us)
                break;
        }
    }
}

/**
 * delay_ms() - ms级别的延时函数
 * 
 * @ms: 要延时的ms数
 * @return: 无
 */
void delay_ms(unsigned int ms)
{
    unsigned int i;
    
    for (i = 0; i < ms; i++)
        delay_us(1000);
}