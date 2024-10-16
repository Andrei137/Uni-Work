.data
    n: .long 10
    v: .long 1, 2, 3, 4, 6, 5, 7, 8, 10, 9
    good: .asciz "Sirul este crescator\n"
    bad: .asciz "Sirul isi strica patternul la pozitia %ld\n"
.text
.globl main
main:
    mov $1, %ecx
    lea v, %esi
    movl (%esi), %eax

etLoop:
    cmp n, %ecx
    je etGood

    movl (%esi, %ecx, 4), %ebx

    cmp %eax, %ebx
    jb etBad

    inc %ecx
    movl %ebx, %eax
    jmp etLoop

etBad:
    dec %ecx
    pushl %ecx
    pushl $bad
    call printf
    popl %ebx
    popl %ebx
    jmp etExit

etGood:
    pushl $good
    call printf
    popl %ebx

etExit:
    pushl $0
    call fflush
    popl %ebx
    
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
