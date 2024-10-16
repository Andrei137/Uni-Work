.data
    x: .long 4
    y: .long 6
    s: .space 4
    show: .asciz "%ld\n"
.text
add:
    pushl %ebp
    mov %esp, %ebp

    movl 8(%ebp), %eax
    addl 12(%ebp), %eax 

    popl %ebp
    ret

.globl main
main:
    movl $5, %eax
    movl $6, %ebx

    pushl %eax
    pushl y
    pushl x
    call add
    mov %eax, s
    popl %edx
    popl %edx
    popl %edx

    pushl s
    pushl $show
    call printf
    popl %ebx
    popl %ebx

et_exit:
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80

