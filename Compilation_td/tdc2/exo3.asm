; registers.asm
section .text
global _start

_start:
   
    mov rbx, 1
    mov r12, 2

    cmp rbx, r12
    jg plus_grand

    
    mov rdi, 0
    jmp fin

    plus_grand:
    
        mov rdi, 1

    fin:
        mov rax, 60     
        syscall

