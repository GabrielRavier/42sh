    .intel_syntax noprefix
    .text

    # We first check whether tz is non-null and then set it to 0, but otherwise we just do the syscall
    .globl my_gettimeofday
    .type my_gettimeofday, @function
    .p2align 4
my_gettimeofday:
    .cfi_startproc

    push rbx
    .cfi_def_cfa_offset 16
    .cfi_offset 3, -16

    test rsi, rsi
    jne .Ltz_non_null

.Ldo_syscall:
    mov eax, 0x60
    syscall

    mov rbx, rax
    cmp rax, -0x1000
    ja .Lset_errno

    pop rbx
    .cfi_remember_state
    .cfi_def_cfa_offset 8

    ret

    .p2align 4
.Lset_errno:
    .cfi_restore_state
    call __errno_location
    neg ebx
    mov [rax], ebx
    mov eax, -1

    pop rbx
    .cfi_remember_state
    .cfi_def_cfa_offset 8
    ret

    .p2align 4
.Ltz_non_null:
    .cfi_restore_state
    mov qword ptr [rsi], 0
    jmp .Ldo_syscall

    .cfi_endproc
    .size my_gettimeofday, . - my_gettimeofday
