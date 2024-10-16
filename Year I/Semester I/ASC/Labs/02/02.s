.data
    x: .space 4
    y: .space 4
    rez1: .space 4
    rez2: .space 4
    pass: .asciz "PASS\n"
    fail: .asciz "FAIL\n"
    fs: .asciz "%ld %ld"
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
    idivl %ebx
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

et_compare:
    movl rez2, %eax
    cmpl rez1, %eax
    jne et_failed

    push $pass

    jmp et_print

et_failed:
    push $fail

et_print:
    call printf
    add $4, %esp

    push $0
    call fflush
    add $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
