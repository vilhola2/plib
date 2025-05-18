.section .note.GNU-stack,"",@progbits
.section .text
.global plib_setjmp
.type plib_setjmp, @function
plib_setjmp:
    # save registers
    mov %rbx, 16(%rdi)
    mov %rbp, 24(%rdi)
    mov %r12, 32(%rdi)
    mov %r13, 40(%rdi)
    mov %r14, 48(%rdi)
    mov %r15, 56(%rdi)

    # save stack pointer
    mov %rsp, 0(%rdi)

    xor %eax, %eax # set return value to 0

    # save return address
    lea .Lreturn_point(%rip), %rax
    mov %rax, 8(%rdi)

    ret # return 0, except if longjmp changed return value

.Lreturn_point:
    ret

.global plib_longjmp
.type plib_longjmp, @function
plib_longjmp:
    # load registers
    mov 16(%rdi), %rbx
    mov 24(%rdi), %rbp
    mov 32(%rdi), %r12
    mov 40(%rdi), %r13
    mov 48(%rdi), %r14
    mov 56(%rdi), %r15

    # restore stack pointer
    mov 0(%rdi), %rsp
    
    # load return value into eax
    mov %esi, %eax # esi is the 2nd arg ( int val )
    test %eax, %eax # make sure its not zero
    jne .Lresume
    mov $1, %eax # if it is, return 1

.Lresume:
    jmp *8(%rdi) # jump to saved rip
