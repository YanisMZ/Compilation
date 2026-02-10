; registers.asm
section .text
global _start
extern show_registers

_start:

    mov rbx, 1
    mov r12,0
    mov r13 ,0
    loop:
        call show_registers 
        cmp rbx , 100
        je end
        add rbx , 9
        jg loop
    end:
        mov rax, 60
	    mov rdi, 0
    syscall
    


