.data
    space: .asciz " "
    new_line: .asciz "\n"
    fs: .asciz "%ld"
.text
proc:
    pushl %ebp
    movl %esp, %ebp

    pushl 8(%ebp)
    push $fs
    call printf
    add $8, %esp

    push $space
    call printf
    add $4, %esp

    cmp $0, 8(%ebp)
    je proc_exit

    movl 8(%ebp), %eax
    decl %eax
    pushl %eax
    call proc
    add $4, %esp

proc_exit:
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
    pushl $fs
    call scanf
    add $8, %esp

    pushl -4(%ebp)
    call proc
    add $4, %esp

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
