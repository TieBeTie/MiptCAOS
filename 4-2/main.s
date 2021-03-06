
.intel_syntax noprefix

# merge sort recursive function
# out should be allocated
# arguments
# l - left bound, r - right bound, in*, out*
.global merge_sort

merge_sort:

    push ebp
    mov ebp, esp

    push ecx
    push ebx
    push eax
    push edi
    push esi
    push edx

    mov eax, [ebp + 8]   #l
    mov ebx, [ebp + 12]  #r

    cmp eax, ebx         # check l < r

    jl next
        cmp eax, ebx
        //jg end           # r > l
        mov eax, [ebp + 16]
        mov eax, [eax + 4 * ebx]
        mov edx, [ebp + 20]
        mov [edx + 4 * ebx], eax
        jmp end

    next:

    mov eax, [ebp + 8]   #l
    mov ebx, [ebp + 12]  #r

    mov ecx, eax
    add ecx, ebx         # l + r

    sar ecx, 1           # mid = (l + r) / 2

    mov edx, ecx
    sub edx, eax

    cmp edx, 0          # mid - l <= 0
    jl sorted1

    push ebp

    push eax            # l
    push ecx            # mid
    push [ebp + 16]     # source
    push [ebp + 20]     # out

    call merge_sort

    add esp, 16         # clear stack (cdecl)

    pop ebp

    sorted1:

    mov eax, [ebp + 8]   #l
    mov ebx, [ebp + 12]  #r

    mov ecx, eax
    add ecx, ebx         # l + r

    sar ecx, 1           # mid = (l + r) / 2

    mov edx, ebx
    sub edx, ecx
    cmp edx, 0           # r - l < 0
    jl sorted2

    push ebp

    mov edx, ecx       # from: mid + 1
    add edx, 1
    push edx
    push ebx           # to: r
    push [ebp + 16]    # source
    push [ebp + 20]    # result

    call merge_sort

    add esp, 16        # clear stack (cdecl)

    pop ebp
    sorted2:
/*
    mov eax, [ebp + 8]   #l
    mov ebx, [ebp + 12]  #r

    mov ecx, eax
    add ecx, ebx         # l + r
    add ecx, 1
    sar ecx, 1           # mid = (l + r) / 2

    mov eax, [ebp + 20]
    add eax, [ebp + 8]
    push eax            # a + left ptr

    mov eax, [ebp + 20] # a + mid + 1
    add eax, ecx
    add eax, 1
    push eax

    mov eax, ecx
    sub eax, [ebp + 8]  # mid - left
    add eax, 1
    push eax

    mov eax, [ebp + 12]
    sub eax, ecx        # right - mid
    push eax

    mov eax, [ebp + 20] # out + left
    add eax, [ebp + 8]
    push eax

    call merge
    add esp, 20         #clear stack (cdecl)
*/
    end:

    pop edx
    pop esi
    pop edi
    pop eax
    pop ebx
    pop ecx

    mov esp, ebp
    pop ebp
    ret

.global merge

# function to merge two sorted arrays and insert them to out.
# !out should be allocated (size = 4*(n1 + n1) bytes)!
# arguments:
# int* in1, int*in2, int n1, int n2, int* out
merge:

    push ebp            # save register
    mov ebp, esp        # ebp = esp

    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov eax, 0          # first array iterator
    mov ebx, 0          # second array iterator

    mov ecx, [ebp + 8]  # first array pointer
    mov edx, [ebp + 12] # second array pointer

    mov esi, [ebp + 16] # first array size
    mov edi, [ebp + 20] # second array size

    main_loop:

      push esi
      push edi

      mov esi, [ecx + eax * 4]
      mov edi, [edx + ebx * 4]
      cmp esi, edi

      jge else

      pop edi
      pop esi

      push   [ecx + eax * 4]                #first element is less than second
      add    eax, 1
      jmp endif

      else:
      pop edi
      pop esi
       push    [edx + ebx * 4]
      add     ebx, 1

      endif:

      cmp eax, esi     #check if one of arrays was finished
      jge end_loop

      cmp ebx, edi
      jge end_loop

      jmp main_loop

    end_loop:


    cmp eax, esi
    jge first_arr_is_empty

    first_arr_loop:

        push [ecx + 4 * eax]
        add eax, 1
        cmp eax, esi
        jl first_arr_loop

    first_arr_is_empty:

    cmp ebx, edi
    jge second_arr_is_empty

    second_arr_loop:

        push [edx + 4 * ebx]
        add ebx, 1
        cmp ebx, edi
        jl second_arr_loop

    second_arr_is_empty:

    mov edx, [ebp + 16]
    add edx, [ebp + 20]  #array size
    mov ebx, [ebp + 24]  # result array pointer

    loop_result:

        pop eax
        sub edx, 1
        mov [ebx + 4 * edx], eax
        cmp edx, 0
        jg loop_result

    mov eax, edx

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx


    mov esp, ebp       # free memory
    pop ebp
    ret
