section .data
seq_numbers: dq 5, 12, 7, 3, 9, 0
section .text
global _start
extern show_registers
extern show_stack
_start:
 call show_stack
    sub rsp, 32        
    mov rbx, rsp 


    mov qword [rbx], 0        ; max = 0
    mov qword [rbx+8], 0      ; min 
    mov qword [rbx+16], 0     ; count = 0
    mov qword [rbx+24], 0     ;somme = 0


    
    mov rsi, seq_numbers     
.loop:
    mov rax, [rsi]       
    cmp rax, 0
    je .done             

    ; max 
    mov rcx, [rbx]
    cmp rax, rcx
    jle .skip_max
    mov [rbx], rax
.skip_max:

    ; min 
    mov rcx, [rbx+8]
    cmp rax, rcx
    jge .skip_min
    mov [rbx+8], rax
.skip_min:

    ; count 
    mov rcx, [rbx+16]
    inc rcx
    mov [rbx+16], rcx

    ;  sum 
    mov rcx, [rbx+24]
    add rcx, rax
    mov [rbx+24], rcx

    add rsi, 8          
    jmp .loop

.done:
    call show_stack

    mov rbx,[rbx] 
    mov r12, [rbx + 8]
    ;mov r13, [rbx + 16]
    ;mov r14, [rbx + 24]
    call show_registers
    mov rax, 60
    mov rdi, 0
    syscall
