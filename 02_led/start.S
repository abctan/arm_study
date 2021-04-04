.global _start

_start:
    # 进入SVC模式
    mrs r0, cpsr
    bic r0, #0x1F
    orr r0, #0x13
    mrs r0, cpsr

    ldr sp, =0x80200000

    b main
    