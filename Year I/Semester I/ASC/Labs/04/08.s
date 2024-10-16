.data
    fact: .long 1
    new_line: .asciz "\n"
    fs: .asciz "%ld"
.text
factorial:
    pushl %ebp
    movl %esp, %ebp

    cmp $1, 8(%ebp)
    je factorial_exit

    mov fact, %eax
    mov 8(%ebp), %ecx
    mull %ecx
    mov %eax, fact

    movl 8(%ebp), %eax
    decl %eax
    pushl %eax
    call factorial
    add $4, %esp

factorial_exit:
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
    call factorial
    add $4, %esp

    push fact
    pushl $fs
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
