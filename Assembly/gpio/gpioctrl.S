.global _start

_start:
/* 1、使能时钟 */
ldr r0, =0x020c4068     /* 将寄存器地址CCM_CCGR0写入到r0 */
ldr r1, =0xffffffff     /* 将所有外设时钟使能 */
str r1,[r0]

ldr r0, =0x020c406c     /* 将寄存器地址CCM_CCGR1写入到r0 */
str r1,[r0]

ldr r0, =0x020c4070     /* 将寄存器地址CCM_CCGR2写入到r0 */
str r1,[r0]

ldr r0, =0x020c4074     /* 将寄存器地址CCM_CCGR3写入到r0 */
str r1,[r0]

ldr r0, =0x020c4078     /* 将寄存器地址CCM_CCGR4写入到r0 */
str r1,[r0]

ldr r0, =0x020c407c     /* 将寄存器地址CCM_CCGR5写入到r0 */
str r1,[r0]

ldr r0, =0x020c4080     /* 将寄存器地址CCM_CCGR6写入到r0 */
str r1,[r0]


/* 2、设置GPIO1_IO08引脚IO复用为GPIO1_IO08 */
ldr r0, =0x020e007c /* 将寄存器IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08写入r0 */
ldr r1, =0x5    /* 设置IO引脚复用模式为GPIO1_IO08 */
str r1,[r0]

/* 3、配置GPIO1_IO08引脚电气属性 
 * bit [16]: 0 关闭HYS
 * bit [15:14]: 00 默认下拉
 * bit [13]: 0 keeper
 * bit [12]: 1 pull/keeper使能
 * bit [11]: 0 禁止开路输出
 * bit [7:6]: 10 速度为100MHz
 * bit [5:3]: 110 驱动能力为R0/6
 * bit [0]: 0 低摆率
 */
ldr r0, =0x020e0308   /* 将寄存器IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO08写入r0 */
ldr r1, =0x10b0 /* 设置GPIO1_IO08引脚电气属性 */
str r1,[r0]

/* 4、配置GPIO1_IO08引脚方向为输出 */
ldr r0, =0x0209c004     /* 将寄存器GPIO1_GDIR地址写入r0 */
ldr r1, =0x00000100     /* 将GPIO1_IO08方向设置为输出 */
str r1,[r0]

/* 5、控制GPIO1_IO08引脚电平高低 */
ldr r0, =0x0209c000     /* 将寄存器GPIO1_DR地址写入r0 */
ldr r1, =0x00000100     /* 将GPIO1_IO08引脚设置为高电平 */ 
str r1,[r0]