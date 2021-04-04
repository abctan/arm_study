.global _start

_start:
    # 1、使能时钟 CCM_CCGR2
    ldr r0, =0x020C4070
    ldr r1, =0xFFFFFFFF
    str r1, [r0]
    # 2、配置IO复用功能
    ldr r0, =0x020E0068
    ldr r1, =0x5
    str r1, [r0]
    # 3、配置IO属性
    ldr r0, =0x020E02F4
    ldr r1, =0x10B0
    str r1, [r0]
    # 4、使能GPIO_01总开关 
    ldr r0, =0x0209C004
    ldr r1, =0x8
    str r1, [r0]
    # 5、打开LED,设置输出低电平
    ldr r0, =0x0209C000
    ldr r1, =0
    str r1, [r0]

boop:
    b boop
    