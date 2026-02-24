; little_endian.asm
section .data
seq_numbers: dw 1, 2, 6, 3, 4, 22, 10, 0
section .text
global _start
extern show_registers
_start:
    mov rbx, 0
    mov r12, seq_numbers
    mov r13, 5
    mov r14, 0
    mov bl, byte [r12+r13*2]        ;[r12 + 10]
    call show_registers
    ; après copie sur 1 octet
    mov r14d, dword [r12+2]
    ; après copie sur 4 octets
    call show_registers
    mov rax, 60
    mov rdi, 0
    syscall
