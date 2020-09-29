.text
.global main

main:

    push lr

    loop:

        ldr r0, stdin_l
        ldr r0, [r0]
        bl fgetc

        cmp r0, #-1
        popeq pc

        cmp r0, #48
        blt loop

        cmp r0, #58
        bgt loop

        ldr r1, stdout_l
        ldr r1, [r1]
        bl fputc
        b loop

stdin_l:
    .word stdin
stdout_l:
    .word stdout
