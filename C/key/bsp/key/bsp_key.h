#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "imx6ul.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"

/* 定义按键值 */
enum _key_value {
    KEY_NONE = 0,
    KEY0_VALUE,
} key_value;

/* 和按键操作相关函数声明 */
void key_init(void);
int key_get_value(void);

#endif