.data
    newline: .asciz "\n"
    fs: .asciz "%ld"
.text
perfect:
    pushl %ebp
    movl %esp, %ebp

    push $0

    xorl %edx, %edx
    movl 8(%ebp), %eax
    movl $2, %ecx
    divl %ecx

    pushl %eax

    mov $1, %ecx

perfect_loop:
    cmpl -8(%ebp), %ecx
    jg perfect_loop_end

    xorl %edx, %edx
    movl 8(%ebp), %eax
    divl %ecx

    cmp $0, %edx
    je perfect_loop_div

    incl %ecx
    jmp perfect_loop

perfect_loop_div:
    addl %ecx, -4(%ebp)
    incl %ecx
    jmp perfect_loop

perfect_loop_end:
    movl -4(%ebp), %eax
    cmp %eax, 8(%ebp)
    je perfect_true

    xorl %eax, %eax
    jmp perfect_end

perfect_true:
    mov $1, %eax

perfect_end:
    add $8, %esp

    popl %ebp
    ret

.globl main
main:
    pushl %ebp
    movl %esp, %ebp

    sub $404, %esp

    movl %ebp, %eax
    subl $4, %eax
    pushl %eax
    push $fs
    call scanf
    add $8, %esp

    xorl %ecx, %ecx

et_loop:
    cmpl -4(%ebp), %ecx
    je et_loop_end

    movl %ebp, %eax
    sub $404, %eax
    sal $2, %ecx
    addl %ecx, %eax
    sar $2, %ecx

    pushl %ecx
    pushl %eax
    push $fs
    call scanf
    add $8, %esp
    popl %ecx

    incl %ecx
    jmp et_loop

et_loop_end:
    xorl %ecx, %ecx
    pushl $0

et_count:
    cmp -4(%ebp), %ecx
    je et_print_end
    
    pushl %ecx
    pushl -404(%ebp, %ecx, 4)
    call perfect
    add $4, %esp
    popl %ecx

    cmp $1, %eax
    je et_count_true

    incl %ecx
    jmp et_count

et_count_true:
    incl -408(%ebp)
    incl %ecx
    jmp et_count

et_print_end:
    pushl -408(%ebp)
    push $fs
    call printf
    add $8, %esp

    push $newline
    call printf
    add $4, %esp

    push $0
    call fflush
    add $4, %esp

    add $409, %esp
    popl %ebp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
