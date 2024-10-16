.data
    s: .space 100
    fs: .asciz "%ld\n"
.text
atoi:
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    mov 8(%ebp), %esi

    push $s
    call strlen
    add $4, %esp

    push $0
    xorl %ecx, %ecx

atoi_loop:
    cmp %eax, %ecx
    je atoi_loop_end

    mov (%esi, %ecx, 1), %edx
    and $0xf, %edx

    cmp $9, %edx
    jle atoi_compare_with_0

    xorl %eax, %eax
    add $4, %esp
    jmp atoi_end

atoi_compare_with_0:
    cmp $0, %edx
    jge atoi_update

    xorl %eax, %eax
    addl $4, %esp
    jmp atoi_end

atoi_update:
    pushl %eax
    pushl %ecx
    pushl %edx
    movl -8(%ebp), %eax
    mov $10, %ecx
    mull %ecx
    popl %edx
    addl %edx, %eax
    movl %eax, -8(%ebp)
    popl %ecx
    popl %eax

    incl %ecx
    jmp atoi_loop

atoi_loop_end:
    movl -8(%ebp), %eax
    add $4, %esp

atoi_end:
    popl %esi
    popl %ebp
    ret

.globl main
main:
    pushl %ebp
    movl %esp, %ebp

    push $s
    call gets
    add $4, %esp

    push $s
    call atoi
    add $4, %esp

    pushl %eax
    push $fs
    call printf
    add $8, %esp

    push $0
    call fflush
    add $4, %esp

    popl %ebp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
