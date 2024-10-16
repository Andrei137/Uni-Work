.data
    var: .long 4
    fs1: .asciz "%ld "
    fs2: .asciz "\n"
.text
proc:
    pushl %ebp
    movl %esp, %ebp

    pushl 8(%ebp)
    pushl $fs1
    call printf
    addl $8, %esp

    cmp $0, 8(%ebp)
    je salt
    mov 8(%ebp), %eax
    dec %eax

    pushl %eax
    call proc
    addl $4, %esp

salt:
    pop %ebp
    ret
    
.globl main 
main:
    pushl var
    call proc
    addl $4, %esp

    pushl $fs2
    call printf
    addl $4, %esp

et_exit:
    mov $1, %eax
    xor %ebx, %ebx
    int $0x80
