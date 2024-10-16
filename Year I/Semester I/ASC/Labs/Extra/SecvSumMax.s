.data
    max: .long 0
    sum: .long 0
    poz: .long 0
    x: .space 4
    n: .space 4
    k: .space 4
    readElement: .asciz "%ld"
    readLenAndK: .asciz "%ld %ld"
    show: .asciz "Prima secventa cu suma maxima %ld incepe pe pozitia %ld\n"
    v: .space 400
.text
.globl main
main:
    pushl $k
    pushl $n
    pushl $readLenAndK
    call scanf
    popl %ebx
    popl %ebx
    popl %ebx

    lea v, %edi
    mov $0, %ecx
etLoop:
    cmp %ecx, n
    je etInit

    pusha
    pushl $x
    pushl $readElement
    call scanf
    popl %ebx
    popl %ebx
    popa

    mov x, %eax
    mov %eax, (%edi, %ecx, 4)

    inc %ecx
    jmp etLoop

etInit:
    mov $0, %ecx
    mov $0, %edx

etFirstSum:
    cmp %ecx, k
    je etInitMax

    mov (%edi, %ecx, 4), %eax
    add %eax, sum

    inc %ecx
    jmp etFirstSum

etInitMax:
    mov sum, %eax
    mov %eax, max

etSum:
    cmp %ecx, n
    je etShow

    mov (%edi, %edx, 4), %eax
    sub %eax, sum
    inc %edx

    mov (%edi, %ecx, 4), %eax
    add %eax, sum
    inc %ecx

    mov sum, %eax
    cmp %eax, max
    jl etNewMax

    jmp etSum

etNewMax:
    mov %eax, max
    mov %edx, poz
    jmp etSum

etShow:
    pushl poz
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
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
