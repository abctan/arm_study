.global _start
.global _bss_start

_bss_start:
    .word __bss_start

.global _bss_end
_bss_end:
    .word __bss_end


_start:
    # 进入SVC模式
    mrs r0, cpsr
    bic r0, #0x1F
    orr r0, #0x13
    mrs r0, cpsr

    # 清除bss段
    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0x0
bss_loop:
    stmia r0!, {r2}
    cmp r0, r1
    ble bss_loop      /* 小于等于继续循环 */


    ldr sp, =0x80200000

    b main
    