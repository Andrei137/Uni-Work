.data
    new_line: .asciz "\n"
    format_scan: .asciz "%ld"
    format_print_without_space: .asciz "%ld"
    format_print_with_space: .asciz "%ld "
.text
# matrix_copy(m1, m2, n)
matrix_copy:
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi

    # n -> n^2
    movl 16(%ebp), %eax
    xorl %edx, %edx
    mull 16(%ebp)
    movl %eax, 16(%ebp)

    movl 8(%ebp), %esi
    movl 12(%ebp), %edi

    xorl %ecx, %ecx

matrix_copy_loop:
    cmp 16(%ebp), %ecx
    je matrix_copy_end

    movl (%esi, %ecx, 4), %eax
    movl %eax, (%edi, %ecx, 4)

    incl %ecx
    jmp matrix_copy_loop

matrix_copy_end:
    popl %edi
    popl %esi
    popl %ebp
    ret

# matrix_print(m1, n) pt debug
matrix_print:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi

    movl 8(%ebp), %esi

    xorb %ch, %ch

matrix_print_first_for:
    cmpb 12(%ebp), %ch
    je matrix_print_end

    xorb %cl, %cl

matrix_print_second_for:
    cmpb 12(%ebp), %cl
    je matrix_print_new_line

    # %eax = %ch * nr_noduri + %cl
    xorl %eax, %eax
    xorl %edx, %edx
    movb %ch, %al
    mull 12(%ebp)
    addb %cl, %al

    # afisare matrice[%ch][%cl] -> -40008(%ebp) + 4 * %eax
    pushl %ecx
    pushl (%esi, %eax, 4)
    pushl $format_print_with_space
    call printf
    addl $8, %esp
    popl %ecx

    pushl %ecx
    pushl $0
    call fflush
    addl $4, %esp
    popl %ecx

    incb %cl
    jmp matrix_print_second_for

matrix_print_new_line:
    pushl %ecx
    pushl $new_line
    call printf
    addl $4, %esp
    popl %ecx

    pushl %ecx
    pushl $0
    call fflush
    addl $4, %esp
    popl %ecx

    incb %ch
    jmp matrix_print_first_for

matrix_print_end:
    popl %esi
    popl %ebx
    popl %ebp
    ret

# matrix_mult(m1, m2, mres, n)
matrix_mult:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 16(%ebp), %edi

    xorb %ch, %ch

matrix_mult_first_for:
    cmpb 20(%ebp), %ch
    je matrix_mult_end

    xorb %cl, %cl

matrix_mult_second_for:
    cmpb 20(%ebp), %cl
    je matrix_mult_increment

    # alocare suma -> -16(%ebp)
    pushl $0 
    xorb %bl, %bl

matrix_mult_third_for:
    cmpb 20(%ebp), %bl
    je matrix_mult_sum

    pushl %ebx

    # %eax = %ch * nr_noduri + %bl
    pushl %ecx
    xorl %eax, %eax
    xorl %edx, %edx
    movb %ch, %al
    mull 20(%ebp)
    addb %bl, %al
    popl %ecx

    # %eax = m1[%ch][%bl]
    movl 8(%ebp), %esi
    movl (%esi, %eax, 4), %eax

    # %eax = %bl * nr_noduri + %cl
    pushl %ecx
    pushl %eax
    xorl %eax, %eax
    xorl %edx, %edx
    movb %bl, %al
    mull 20(%ebp)
    addb %cl, %al

    # %ebx = m2[%bl][%cl]
    movl 12(%ebp), %esi
    movl (%esi, %eax, 4), %ebx
    popl %eax
    popl %ecx

    # %eax = %eax * %ebx
    xorl %edx, %edx
    mull %ebx
    
    # sum += %eax
    addl %eax, -16(%ebp)

    popl %ebx

    incb %bl
    jmp matrix_mult_third_for

matrix_mult_sum:
    # %eax = %ch * nr_noduri + %cl
    xorl %eax, %eax
    xorl %edx, %edx
    movb %ch, %al
    mull 20(%ebp)
    addb %cl, %al

    # mrez[%ch][%cl] = sum
    movl -16(%ebp), %ebx
    movl %ebx, (%edi, %eax, 4)

    # dezalocare suma
    addl $4, %esp

    incb %cl
    jmp matrix_mult_second_for

matrix_mult_increment:
    incb %ch
    jmp matrix_mult_first_for

matrix_mult_end:
    popl %edi
    popl %esi
    popl %ebx
    popl %ebp
    ret

.globl main
main:
    pushl %ebp
    movl %esp, %ebp

    # alocare cerinta si numar de noduri
    subl $8, %esp

    # citire cerinta -> -4(%ebp)
    movl %ebp, %eax
    subl $4, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp

    # citire numar de noduri -> -8(%ebp)
    movl %ebp, %eax
    subl $8, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp

    # alocare matrice[100][100]
    subl $40000, %esp

     # alocare vector[100]
    subl $400, %esp

    xorl %ecx, %ecx

et_scan:
    cmp -8(%ebp), %ecx
    je et_scan_end

    # citire numar de legaturi -> -40408(%ebp) + 4 * %ecx
    movl %ebp, %eax
    subl $40408, %eax
    pushl %ecx
    shll $2, %ecx
    addl %ecx, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp
    popl %ecx

    incl %ecx
    jmp et_scan

et_scan_end:
    xorb %ch, %ch

et_create_matrix_first_for:
    cmpb -8(%ebp), %ch
    je et_query

    xorb %cl, %cl

et_create_matrix_second_for:
    movb %ch, %al
    movb $0, %ah
    cmpb -40408(%ebp, %eax, 4), %cl
    je et_create_matrix_second_for_end

    # alocare temp_value
    subl $4, %esp

    # citire temp_value -> -40412(%ebp)
    movl %ebp, %eax
    subl $40412, %eax
    pushl %ecx
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp
    popl %ecx

    # matrice[%ecx][temp_value] = 1 -> -40008(%ebp) + 4 * (%ecx * nr_noduri + temp_value)
    xorl %eax, %eax
    xorl %edx, %edx
    movb %ch, %al
    mull -8(%ebp)
    addl -40412(%ebp), %eax
    movl $1, -40008(%ebp, %eax, 4)

    # dezalocare temp_value
    addl $4, %esp

    incb %cl
    jmp et_create_matrix_second_for

et_create_matrix_second_for_end:
    incb %ch
    jmp et_create_matrix_first_for

et_query:
    # dezalocare vector[100]
    addl $400, %esp

    xorb %ch, %ch

    cmp $2, -4(%ebp)
    je et_copy_matrix

# cerinta 1
et_print_1:
    xorb %ch, %ch

et_print_1_first_for:
    cmpb -8(%ebp), %ch
    je et_dealloc

    xorb %cl, %cl

et_print_1_second_for:
    cmpb -8(%ebp), %cl
    je et_print_1_new_line

    # %eax = %ch * nr_noduri + %cl
    xorl %eax, %eax
    xorl %edx, %edx
    movb %ch, %al
    mull -8(%ebp)
    addb %cl, %al

    movl %eax, %ebx

    # afisare matrice[%ch][%cl] -> -40008(%ebp) + 4 * %eax
    pushl %ecx
    movl %ebp, %eax
    subl $40008, %eax
    pushl (%eax, %ebx, 4)
    pushl $format_print_with_space
    call printf
    addl $8, %esp
    popl %ecx

    pushl %ecx
    pushl $0
    call fflush
    addl $4, %esp
    popl %ecx

    incb %cl
    jmp et_print_1_second_for

et_print_1_new_line:
    pushl %ecx
    pushl $new_line
    call printf
    addl $4, %esp
    popl %ecx

    pushl %ecx
    pushl $0
    call fflush
    addl $4, %esp
    popl %ecx

    incb %ch
    jmp et_print_1_first_for

# cerinta 2
et_copy_matrix:
    # alocare matrice[100][100]
    subl $40000, %esp

    # copiere m1 in m2 -> -80008(%ebp)
    pushl -8(%ebp)
    movl %ebp, %eax
    subl $80008, %eax
    pushl %eax
    movl %ebp, %eax
    subl $40008, %eax
    pushl %eax
    call matrix_copy
    addl $12, %esp

et_scan_length:
    # alocare lungime
    subl $4, %esp

    # citire lungime -> -80012(%ebp)
    movl %ebp, %eax
    subl $80012, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp

    decl -80012(%ebp)

    xorl %ecx, %ecx

et_for_length:
    cmp -80012(%ebp), %ecx
    je et_print_2

    # alocare mres[100][100]
    subl $40000, %esp

    # mres = m1 * m2 -> -120012(%ebp)
    pushl %ecx
    pushl -8(%ebp)
    movl %ebp, %eax
    subl $120012, %eax
    pushl %eax
    movl %ebp, %eax
    subl $80008, %eax
    pushl %eax
    movl %ebp, %eax
    subl $40008, %eax
    pushl %eax
    call matrix_mult
    addl $16, %esp
    popl %ecx

    # copiere mres in m2 -> -80008(%ebp)
    pushl %ecx
    pushl -8(%ebp)
    movl %ebp, %eax
    subl $80008, %eax
    pushl %eax
    movl %ebp, %eax
    subl $120012, %eax
    pushl %eax
    call matrix_copy
    addl $12, %esp
    popl %ecx

    # dezalocare mres[100][100]
    addl $40000, %esp

    incl %ecx
    jmp et_for_length

et_print_2:
    pushl -8(%ebp)
    movl %ebp, %eax
    subl $40008, %eax
    pushl %eax
    movl %ebp, %eax
    subl $80008, %eax
    pushl %eax
    call matrix_copy
    addl $12, %esp

    # dezalocare matrice[100][100] si lungime
    addl $40004, %esp

    # alocare noduri sursa si destinatie
    subl $8, %esp

    # citire nod sursa -> -40012(%ebp)
    movl %ebp, %eax
    subl $40012, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp

    # citire nod destinatie -> -40016(%ebp)
    movl %ebp, %eax
    subl $40016, %eax
    pushl %eax
    pushl $format_scan
    call scanf
    addl $8, %esp

    movl -40012(%ebp), %eax
    movl -40016(%ebp), %ebx

    # dezalocare noduri sursa si destinatie
    addl $8, %esp

    # %eax = %eax * nr_noduri + %ebx
    xorl %edx, %edx
    mull -8(%ebp)
    addl %ebx, %eax

    # afisare matrice[%eax]
    pushl -40008(%ebp, %eax, 4)
    pushl $format_print_without_space
    call printf
    addl $8, %esp

    pushl $0
    call fflush
    addl $4, %esp

et_dealloc:
    # dezalocare cerinta, numar de noduri si matrice[100][100]
    addl $40008, %esp
    popl %ebp

et_exit:
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80
