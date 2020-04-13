.global _start

/*
 *  _start函数，程序先在这开始执行，用来设置C语言运行环境
 */
_start:
    /* SoC进入SVC运行模式 */
    mrs r0, cpsr
    bic r0, r0, #0x1f   /* 将cpsr寄存器的M[4:0]清0 */
    orr r0, r0, #0x13   /* SoC使用SVC运行模式 */
    msr cpsr,   r0

    /* 设置C语言运行环境 */
    ldr sp, =0x80200000 /* 设置栈指针 */
    b main      /* 跳转到C语言的main()函数执行 */
