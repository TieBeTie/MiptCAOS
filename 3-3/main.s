.text
.global main

main:

    push { r4-r7, ip, lr }

    mov r4, #1
    lsl r4, #10

    mov r0, r4     // malloc argument
    bl malloc      // call malloc
    mov r5, r0     // data start pointer
    mov r6, #0     // data iterator

    loop:

        sub r6, #1
        cmp r6, r4
        bne enough_mem
            lsl r4, #1
            mov r0, r5
            mov r1, r4
            bl realloc
            mov r5, r0
        enough_mem:
        add r6, #1
        ldr r0, stdin_l
        ldr r0, [r0]
        bl fgetc
        cmp r0, #-1
        strne r0, [r5, r6]   // load char if not EOF
        addne r6, #1
        bne loop

    sub r6, #1

    loop_reverse:

        cmp r6, #-1
        beq end_loop
        ldrne r0, [r5, r6]
        ldrne r1, stdout_l
        ldrne r1, [r1]
        bl fputc
        sub r6, #1

        b loop_reverse

    end_loop:

    mov r0, r5
    bl free
    pop { r4-r7, ip, pc }

stdin_l:
    .word stdin
stdout_l:
    .word stdout
