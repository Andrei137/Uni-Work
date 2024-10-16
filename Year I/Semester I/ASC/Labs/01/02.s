.data
    s: .space 12
.text
.globl main
main:
    mov $3, %eax
    mov $0, %ebx
    mov $s, %ecx
    mov $12, %edx 
    int $0x80

et_show:
    push $s
    call printf
    add $4, %esp

    push $0
    call fflush
    add $4, %esp

et_exit:
    mov $1, %eax
    xorl %ebx, %ebx
    int $0x80
