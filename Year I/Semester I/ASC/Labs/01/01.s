.data
    new_line: .asciz "\n"
    fs: .asciz "%ld %ld"
    x: .space 4
    y: .space 4
.text
.globl main
main:
    pushl $y
    pushl $x
    pushl $fs
    call scanf
    addl $12, %esp

et_change:
    movl x, %eax
    movl y, %ebx

    xorl %ebx, %eax
    xorl %eax, %ebx
    xorl %ebx, %eax 

    movl %eax, x
    movl %ebx, y

et_print:
    pushl y
    pushl x
    pushl $fs
    call printf
    addl $12, %esp

    push $new_line
    call printf
    addl $4, %esp

    pushl $0
    call fflush
    addl $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
