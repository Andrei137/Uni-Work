.data
    n1: .long 3
    n2: .long 0
    k: .long 3
    fs: .asciz "%ld\n"
.text
rest:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    mov 8(%ebp), %eax
    mov 12(%ebp), %ebx
    xor %edx, %edx

    div %ebx

    mov %edx, %eax

    pop %ebx
    pop %ebp
    ret
proc:
    pushl %ebp
    mov %esp, %ebp

    sub $4, %esp

    mov 8(%ebp), %eax
    add 12(%ebp), %eax

    mov %eax, -4(%ebp)

    pushl 16(%ebp)
    pushl -4(%ebp)
    call rest
    add $8, %esp

    add $4, %esp
    pop %ebp
    ret
.globl main
main:
    pushl k
    pushl n2
    pushl n1
    call proc
    add $12, %esp

    push %eax
    pushl $fs
    call printf
    add $8, %esp

et_exit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80

# mov 8(%edp), %edi
# mov %ebp, %edi
# sub $400, %edi
# mov $2, %ecx
# movl $5, 9%edi, %edx, 4)