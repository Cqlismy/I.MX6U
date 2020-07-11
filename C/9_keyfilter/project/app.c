#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_epit.h"
#include "bsp_keyfilter.h"

/**
 * main() - 主函数
 */
int main(void)
{
    interrupt_init();           /* 中断初始化 */
    imx6ul_clk_init();          /* 初始化相关时钟 */
    system_clk_enable();        /* 系统外设时钟使能 */
    led_init();                 /* LED灯初始化 */
    epit1_init(66, 1000000);    /* EPIT1定时器初始化 */
    keyfilter_init();           /* 按键初始化(EPIT2定时器消抖) */

    while (1) {

    }

    return 0;
}
