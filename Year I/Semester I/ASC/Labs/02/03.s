.data
    a: .space 4
    b: .space 4
    c: .space 4
    min: .space 4
    format_print: .asciz "%ld\n"
    format_scan: .asciz "%ld %ld %ld"
.text
.globl main
main:
    pushl $c
    pushl $b
    pushl $a
    push $format_scan
    call scanf
    add $16, %esp

    movl a, %eax
    cmpl b, %eax
    jle et_a_below

    movl b, %eax
    cmpl c, %eax
    jle et_b_lowest

    movl c, %eax
    movl %eax, min
    jmp et_print

et_a_below:
    cmpl c, %eax
    jle et_a_lowest

    movl c, %eax
    movl %eax, min
    jmp et_print

et_a_lowest:
    movl a, %eax
    movl %eax, min
    jmp et_print

et_b_lowest:
    movl b, %eax
    movl %eax, min

et_print:
    pushl min
    push $format_print
    call printf
    add $8, %esp

    pushl $0
    call fflush
    add $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
