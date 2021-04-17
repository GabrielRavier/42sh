    .intel_syntax noprefix
    .text

    # This is implemented as an infinite loop of using the exit syscall, then the exit_group syscall and finally using hlt
    .globl my__exit
    .type my__exit, @function
    .p2align 4
my__exit:
    .cfi_startproc

    sub rsp, 24
    .cfi_def_cfa_offset 32

    mov [rsp + 12], edi
    call __errno_location
    mov edi, [rsp + 12]
    mov r8, rax
    mov esi, 231
    mov edx, 60
    jmp .Ldo_exit_group_syscall

.Ldo_exit_syscall:
    mov eax, edx
    syscall
    cmp rax, -0x1000
    ja .Lset_errno_exit

.Ldo_hlt:
    hlt

.Ldo_exit_group_syscall:
    mov eax, esi
    syscall
    cmp rax, -0x1000
    jbe .Ldo_exit_syscall

    mov [r8], eax
    jmp .Ldo_exit_syscall

.Lset_errno_exit:
    mov [r8], eax
    jmp .Ldo_hlt
    
    .cfi_endproc
    .size my__exit, . - my__exit
