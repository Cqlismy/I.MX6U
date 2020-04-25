#ifndef __APP_H
#define __APP_H

/**
 *  SoC中CCM_CCGR寄存器地址
 */
#define CCM_CCGR0   *((volatile unsigned int *)0x020c4068)
#define CCM_CCGR1   *((volatile unsigned int *)0x020c406c)
#define CCM_CCGR2   *((volatile unsigned int *)0x020c4070)
#define CCM_CCGR3   *((volatile unsigned int *)0x020c4074)
#define CCM_CCGR4   *((volatile unsigned int *)0x020c4078)
#define CCM_CCGR5   *((volatile unsigned int *)0x020c407c)
#define CCM_CCGR6   *((volatile unsigned int *)0x020c4080)

/**
 *  SoC中IOMUXC中CSI_DATA00引脚复用配置寄存器地址
 */
#define SW_MUX_CTL_PAD_CSI_DATA00   *((volatile unsigned int *)0x020e01e4)
#define SW_PAD_CTL_PAD_CSI_DATA00   *((volatile unsigned int *)0x020e0470)

/**
 *  SoC中GPIO4寄存器相关地址
 */
#define GPIO4_DR        *((volatile unsigned int *)0x020a8000)
#define GPIO4_GDIR      *((volatile unsigned int *)0x020a8004)
#define GPIO4_PSR       *((volatile unsigned int *)0x020a8008)
#define GPIO4_ICR1      *((volatile unsigned int *)0x020a800c)
#define GPIO4_ICR2      *((volatile unsigned int *)0x020a8010)
#define GPIO4_IMR       *((volatile unsigned int *)0x020a8014)
#define GPIO4_ISR       *((volatile unsigned int *)0x020a8018)
#define GPIO4_EDGE_SEL  *((volatile unsigned int *)0x020a801c)

#endif
