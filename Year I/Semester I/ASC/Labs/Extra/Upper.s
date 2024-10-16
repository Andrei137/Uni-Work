.data
    s: .space 100
    sLen: .space 4
    show: .asciz "%s\n"
.text
.globl main
main:
    pushl $s
    call gets
    popl %ebx

    pushl $s
    call strlen
    popl %ebx

    mov %eax, sLen
    lea s, %esi
    mov $0, %ecx

etLoop:
    cmp %ecx, sLen
    je etShow

    sub $32, (%esi, %ecx, 1)

    inc %ecx
    jmp etLoop

etShow:
    pushl $s
    pushl $show
    call printf
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

etExit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80