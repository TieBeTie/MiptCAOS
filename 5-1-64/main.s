.intel_syntax noprefix

.global _start

_start:

    .loop:

       mov rax, 0
       mov rdi, 0
       lea rsi, hello
       mov rdx, 1
       syscall

       cmp rax, 0
       jle end_loop

       mov rax, 1
       mov rdi, 1
       lea rsi, hello
       mov rdx, 1
       syscall

       jmp .loop

    end_loop:

    mov rax, 60
    mov rbx, 0
    syscall

.data
hello:
    .byte 1

