.data
    n: .space 4
    format_scan: .asciz "%ld"
    is_prime: .asciz "The number %ld is prime\n"
    is_not_prime: .asciz "The number %ld is not prime\n"
.text
.globl main
main:
    pushl $n
    push $format_scan
    call scanf
    addl $8, %esp

    pushl n

    movl n, %eax
    cmp $0, %eax
    je et_not_prime

    cmp $1, %eax
    je et_not_prime

    cmp $2, %eax
    je et_prime

    mov $0, %edx
    mov $2, %ebx
    divl %ebx

    cmp $0, %edx
    je et_not_prime

    mov $3, %ecx

et_loop:
    cmpl n, %ecx
    jae et_prime

    movl n, %eax
    movl %ecx, %ebx
    mov $0, %edx
    divl %ebx

    cmpl $0, %edx
    je et_not_prime

    add $2, %ecx
    jmp et_loop

et_not_prime:
    push $is_not_prime
    jmp et_print

et_prime:
    push $is_prime
    
et_print:
    call printf
    addl $8, %esp

    push $0
    call fflush
    addl $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
