    .intel_syntax noprefix
    .text

    .globl SYSCALL_SYMBOL
    .type SYSCALL_SYMBOL, @function
    .p2align 4
SYSCALL_SYMBOL:
    .cfi_startproc

    mov eax, SYSCALL_NUMBER
    syscall

    cmp rax, -0x1000
    ja .Lset_errno

    ret

    .p2align 4
.Lset_errno:
    push rbx
    .cfi_def_cfa_offset 16
    .cfi_offset 3, -16

    mov rbx, rax
    neg ebx
    call __errno_location
    mov [rax], ebx
    mov eax, -1

    pop rbx
    .cfi_def_cfa_offset 8
    ret

    .cfi_endproc
    .size SYSCALL_SYMBOL, . - SYSCALL_SYMBOL

#undef SYSCALL_SYMBOL
#undef SYSCALL_NUMBER
