.data
    format_scan: .asciz "%ld"
    max: .space 4
    ap: .space 4
    n: .space 4
    x: .space 4
    format_print_one: .asciz "Maximul %ld apare o data\n"
    format_print: .asciz "Maximul %ld apare de %ld ori\n"
.text
.globl main
main:
    pushl $n
    push $format_scan
    call scanf
    add $8, %esp

    pushl $x
    push $format_scan
    call scanf
    add $8, %esp

    movl x, %eax
    movl %eax, max
    movl $1, ap
    mov $1, %ecx

et_loop:
    cmp %ecx, n
    je et_print

    pushl %ecx
    pushl $x
    push $format_scan
    call scanf
    add $8, %esp
    popl %ecx

    movl max, %eax

    cmpl x, %eax
    je et_equal
    jl et_greater

    incl %ecx
    jmp et_loop

et_equal:
    incl ap
    incl %ecx
    jmp et_loop

et_greater:
    movl x, %eax
    movl %eax, max
    movl $1, ap

    incl %ecx
    jmp et_loop

et_print:
    cmp $1, ap
    je et_print_one

    pushl ap
    pushl max
    push $format_print
    call printf
    add $12, %esp

    jmp et_flush

et_print_one:
    pushl max
    push $format_print_one
    call printf
    add $8, %esp

et_flush:
    push $0
    call fflush
    add $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
