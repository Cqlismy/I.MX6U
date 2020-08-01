#ifndef __BSP_GPTINT_H
#define __BSP_GPTINT_H

#include "imx6ul.h"

void gpt2_init(unsigned int prescalar, unsigned int value);
void gpt2_irqhandler(unsigned int giccIar, void *userParam);

#endif