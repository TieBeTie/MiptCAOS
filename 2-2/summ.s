   .text
   .global summ

summ:
   // r0 = x0, r1 = N, r2 = X
    cmp r1, #0
    blt end

    cmp r1, #0
    beq end

    loop:

      ldr r3, [r2]    //load from r2

      add r0, r0, r3  // add r4 to result
      add r2, r2, #4  // inc pointer
      sub r1, r1, #1  // dec counter

      cmp r1, #0
      bgt loop

    end:

      bx lr
