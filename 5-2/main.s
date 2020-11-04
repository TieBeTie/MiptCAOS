.intel_syntax noprefix
.global _start
.align 8
.text
  _start:

    mov rax, 12
    mov rdi, 0
    syscall
    mov r14, rax

    mov rax, 12
    lea rdi, [r14 + 60000000]
    syscall

    mov r12, 0
    loop:
    mov rax, 0
    mov rdi, 0
    lea rsi, [r14 + r12]
    mov rdx, 4096
    syscall
    add r12, rax

    cmp rax, 0
    je endloop

    jmp loop
    endloop:

    mov r13, r12
    loop2:
        cmp r13, 0
        je end2
        sub r13, 1
        movzx r15, byte ptr [r14 + r13]
        cmp r15, 10
        jne skipprint
        mov rax, 1
        mov rdi, 1
        lea rsi, [r14 + r13]
        mov rdx, r12
        sub rdx, r13
        syscall
        mov r12, r13
        skipprint:
        jmp loop2
    end2:

    mov rax, 1
    mov rdi, 1
    lea rsi, enter
    mov rdx, 1
    syscall

    mov rax, 1
    mov rdi, 1
    lea rsi, [r14 + r13]
    mov rdx, r12
    sub rdx, r13
    syscall

    mov rax, 12
    lea rdx, [r14 - 60000000]
    syscall

    # exit
    mov rax, 60
    mov rdi, 0
    syscall
.data
    enter:
       .asciz "\n"
