.global my_sin

.intel_syntax noprefix

.text
my_sin:
    push ebp
    mov ebp, esp
    sub esp, 8
    push ebx
    push ecx

    movsd xmm0, [ebp + 8]     # x

    mov eax, 0
    cvtsi2sd xmm1, eax        # sum is 0.0

    mov eax, 1
    cvtsi2sd xmm2, eax        # sign

    mov ebx, 128               # iterations

    mov eax, -1
    cvtsi2sd xmm3, eax        # -1.0 constant

    mov eax, 2
    cvtsi2sd xmm4, eax        # 2.0 constant

    mov eax, 1                # iterations counter

    movsd xmm5, xmm0          # x^(2n-1) / (2n -1)!
    addsd xmm1, xmm5          # sum = x

    loop:

       add eax, 1             # increment
       mulsd xmm5, xmm0       # next pow
       mulsd xmm5, xmm0
       cvtsi2sd xmm6, eax     # n
       mulsd xmm6, xmm4       # 2*n
       addsd xmm6, xmm3       # 2*n - 1
       divsd xmm5, xmm6
       addsd xmm6, xmm3       # 2*n - 2
       divsd xmm5, xmm6
       mulsd xmm5, xmm3       # sign
       addsd xmm1, xmm5

       cmp eax, ebx
       jle loop

    movsd xmm0, xmm1
    movsd [ebp - 8], xmm0
    fld qword ptr [ebp - 8]
    pop ecx
    pop ebx
    leave
    ret

