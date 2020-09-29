    .text
    .global solve

solve:

    push {r4, r5, r6, r7}

    mov r4, #0

    loop:

       mul r5, r0, r4
       mul r5, r4
       mul r5, r4

       mul r6, r1, r4
       mul r6, r4

       mul r7, r2, r4

       add r5, r5, r6
       add r5, r7
       add r5, r3

       cmp r5, #0
       addne r4, #1
       bne loop

    mov r0, r4

    pop {r4, r5, r6, r7}

    bx lr
