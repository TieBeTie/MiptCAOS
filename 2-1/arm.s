    .text
    .global f

f:
    // r0 = A r1 = V r2 = C r3 = x
    // A x^2 + Bx + C
    mul    r0, r0, r3
    mul    r0, r0, r3
    //Bx
    mul   r1, r1, r3
    // sum
    add    r0, r0, r2
    add    r0, r0, r1
    // result
    mov    r1, r0
    // finish function
    bx     lr

     


