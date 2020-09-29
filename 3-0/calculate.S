    .data
    .global R
R:  .space 4

    .text
    .global calculate

calculate:

    push  {r4, r5, r6, r7, r8}

    ldr   r0, .Lexterns
    ldr   r0, [r0]

    ldr   r1, .Lexterns+4
    ldr   r1, [r1]

    ldr   r2, .Lexterns+8
    ldr   r2, [r2]

    ldr   r3, .Lexterns+12
    ldr   r3, [r3]

    mul   r4, r0, r1
    mul   r5, r2, r3
    add   r6, r4, r5

    ldr   r7, .Lexterns+16
    str   r6, [r7]

    pop   {r4, r5, r6, r7, r8}

    bx    lr

.Lexterns:

     .word  A
     .word  B
     .word  C
     .word  D
     .word  R
