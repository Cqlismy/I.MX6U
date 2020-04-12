#include "bsp_delay.h"

/**
 * delay_short() - 短时间延时函数
 * 
 * @n: 要循环的次数
 */
void delay_short(volatile unsigned int n)
{
    while(n--);
}

/**
 * delay() - 延时函数，SoC在396MHz大概延时1ms
 * 
 * @n: 要延时的ms数
 */
void delay(volatile unsigned int n)
{
    while(n--) {
        delay_short(0x07ff);
    }
}