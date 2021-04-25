    .intel_syntax noprefix
    .text

    .globl SYSCALL_SYMBOL
    .type SYSCALL_SYMBOL, @function
    .p2align 4
SYSCALL_SYMBOL:
    .cfi_startproc

    mov eax, SYSCALL_NUMBER
    syscall
    ret

    .cfi_endproc
    .size SYSCALL_SYMBOL, . - SYSCALL_SYMBOL

#undef SYSCALL_SYMBOL
#undef SYSCALL_NUMBER
