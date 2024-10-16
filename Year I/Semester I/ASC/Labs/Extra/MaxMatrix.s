.data
    x: .space 4
    n: .space 4
    m: .space 4
    max: .long 0
    ap: .long 1
    readLength: .asciz "%ld %ld"
    readElement: .asciz "%ld"
    show: .asciz "%ld %ld\n"
.text
.globl main
main:
    pushl $m
    pushl $n
    pushl $readLength
    call scanf
    popl %ebx
    popl %ebx
    popl %ebx

    mov $-1, %ch

etLoop1:
    inc %ch
    cmp %ch, n
    je etShow

    mov $0, %cl
    jmp etLoop2

etLoop2:
    cmp %cl, m
    je etLoop1

    pusha
    pushl $x
    pushl $readElement
    call scanf
    popl %ebx
    popl %ebx
    popa

    movl x, %eax
    cmp %eax, max
    je etIsEqual
    jl etIsGreater

    inc %cl
    jmp etLoop2

etIsEqual:    
    incl ap
    inc %cl
    jmp etLoop2

etIsGreater:
    movl x, %eax
    mov %eax, max
    movl $1, ap
    inc %cl
    jmp etLoop2

etShow:
    pushl ap
    pushl max
    pushl $show
    call printf
    popl %ebx
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

etExit:
    mov $0, %eax
    xor %ebx, %ebx
    int $0x80
