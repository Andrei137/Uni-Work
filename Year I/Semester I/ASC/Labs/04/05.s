.data
    new_line: .asciz "\n"
    fs: .asciz "%ld"
.text
g:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    incl %eax

    popl %ebp
    ret

f:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    pushl %eax
    call g
    add $4, %esp

    mov $2, %ecx
    mull %ecx

    popl %ebp
    ret

.globl main
main:   
    pushl %ebp
    movl %esp, %ebp

    sub $4, %esp

    movl %ebp, %eax
    sub $4, %eax
    pushl %eax
    push $fs
    call scanf
    add $8, %esp

    pushl -4(%ebp)
    call f
    add $4, %esp

    movl %eax, -4(%ebp)

    pushl -4(%ebp)
    push $fs
    call printf
    add $8, %esp

    push $new_line
    call printf
    add $4, %esp

    push $0
    call fflush
    add $4, %esp

    add $4, %esp
    popl %ebp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
