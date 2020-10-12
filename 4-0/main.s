.global summ

.intel_syntax noprefix

.text

summ:

   push ebp
   mov ebp, esp
   mov ecx, [ebp + 8]    # N
   mov eax, 0

   cycle:

      mov edx, [ebp + 12]
      mov edx, [edx + 4 * ecx - 4]
      mov eax, edx
      mov edx, [ebp + 16]
      mov edx, [edx + 4 * ecx - 4]
      add eax, edx
      mov edx, [ebp + 20]
      mov [edx + 4 * ecx - 4], eax

      loop cycle

   pop ebp
   ret

.global apb

apb:
   push ebp
   mov ecx, [esp + 8]
   mov edx, [esp + 12]
   add ecx, edx
   mov eax, ecx
   pop ebp
   ret
