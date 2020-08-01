#ifndef __BSP_KEYFILTER_H
#define __BSP_KEYFILTER_H

#include "imx6ul.h"

/* 相关函数声明 */
void keyfilter_init(void);
void keyfiltertimer_init(unsigned int prescalar, unsigned int value);
void keyfiltergpio_irqhander(unsigned int giccIar, void *userParam);
void keyfiltertimer_irqhandler(unsigned int giccIar, void *userParam);
void keyfiltertimer_start(unsigned int value);
void keyfiltertimer_stop(void);

#endif