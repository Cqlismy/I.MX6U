#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"

/**
 * myapp() - 主函数
 */
int main(void)
{
    clk_enable();   /* 外设时钟使能 */
    gpio_init();    /* GPIO初始化 */

    while (1) {
        gpio_output(hight);
        delay(1000);
        gpio_output(low);
        delay(1000);
    }

    return 0;
}
