.data
    format_print: .asciz "%s\n"
    n: .space 4
    s: .space 100
    t: .space 100
.text
.globl main

main:
    pushl $s
    call gets
    add $4, %esp

    pushl $s
    call strlen
    add $4, %esp

    mov $0, %edx
    movl %eax, n
    movl n, %ecx

    lea s, %esi
    lea t, %edi

et_loop:
    movl -1(%esi, %ecx, 1), %ebx
    movl %ebx, (%edi, %edx, 1)

    incl %edx
    loop et_loop

et_print:
    mov $0, %ebx
    mov %ebx, (%edi, %edx, 1)

    pushl $t
    push $format_print
    call printf
    add $8, %esp

    push $0
    call fflush
    add $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
