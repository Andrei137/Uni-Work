.data
    n: .space 4
    read: .asciz "%ld"
    isPrime: .asciz "The number %ld is prime\n"
    isNotPrime: .asciz "The number %ld is not prime\n"
.text

prime:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax

    cmp $0, %eax
    je etNotPrime

    cmp $1, %eax
    je etNotPrime

    cmp $2, %eax
    je etPrime

    mov $0, %edx
    mov $2, %ebx
    div %ebx
    cmp $0, %edx
    je etNotPrime

    mov $3, %ecx

etLoop:
    cmp n, %ecx
    jae etPrime

    mov n, %eax
    mov %ecx, %ebx
    mov $0, %edx
    div %ebx
    cmp $0, %edx
    je etNotPrime

    add $2, %ecx
    jmp etLoop

etPrime:
    pushl n
    pushl $isPrime
    call printf
    popl %edx
    popl %edx
    popl %ebp
    ret

etNotPrime:
    pushl n
    pushl $isNotPrime
    call printf
    popl %edx
    popl %edx
    popl %ebp
    ret

.globl main

main:
    pushl $n
    pushl $read
    call scanf
    popl %ebx
    popl %ebx

    pushl n
    call prime
    popl %edx

etExit:
    pushl $0
    call fflush
    popl %ebx

    mov $1, %eax
    xor %ebx, %ebx
    int $0x80