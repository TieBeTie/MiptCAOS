.intel_syntax noprefix

.text
.global dot_product

dot_product:
    push ebp
    mov ebp, esp
    push ecx
    push ebx
    push edx

    mov eax, 0
    cvtsi2sd xmm0, eax
    mov edx, [ebp + 8]
    mov eax, [ebp + 12]
    mov ebx, [ebp + 16]

    loop:
        sub edx, 1
        movups xmm1, [eax + edx * 4]
        movups xmm2, [ebx + edx * 4]
        mulss xmm1, xmm2
        addss xmm0, xmm1
        cmp edx, 0
        jne loop

    pop edx
    pop ebx
    pop ecx

    sub esp, 4
    movss [esp], xmm0
    fld dword ptr [esp]
    add esp, 4

    leave
    ret
