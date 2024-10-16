.data
    prop: .space 100
    count: .long 0
    afis: .asciz "%ld\n"
    sep: .asciz " "
.text
.global main

main:
    pushl $prop
    call gets
    popl %ebx

    pushl $sep
    pushl $prop
    call strtok
    popl %ebx
    popl %ebx

    mov %eax, %ecx

etLoop:
    cmp $0, %ecx
    je etExit

    incl count

    pushl $sep
    pushl $0
    call strtok
    popl %ebx
    popl %ebx

    mov %eax, %ecx
    jmp etLoop

etExit:
    movl count, %edx
    pushl %edx
    pushl $afis
    call printf
    popl %ebx
    popl %ebx

    pushl $0
    call fflush
    popl %ebx

    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
