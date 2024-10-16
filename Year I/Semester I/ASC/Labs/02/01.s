.data
    new_line: .asciz "\n"
    fs: .asciz "%ld %ld"
    x: .space 4
    y: .space 4
    rez1: .space 4
    rez2: .space 4
.text
.globl main
main:
    pushl $y
    pushl $x
    push $fs
    call scanf
    add $12, %esp

et_v1:
    mov $0, %edx
    movl x, %eax
    mov $16, %ebx
    idiv %ebx
    movl %eax, %ecx

    movl y, %eax
    mov $16, %ebx
    mull %ebx
    addl %ecx, %eax

    movl %eax, rez1

et_v2:
    movl x, %eax
    shr $4, %eax

    movl y, %ebx
    shl $4, %ebx
    addl %ebx, %eax

    movl %eax, rez2

et_show:
    pushl rez2
    pushl rez1
    push $fs
    call printf
    add $12, %esp

    push $new_line
    call printf
    add $4, %esp

    pushl $0
    call fflush
    add $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
