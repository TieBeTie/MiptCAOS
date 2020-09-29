.data

   int_format: .asciz "%d"
   num_1: .word 0
   num_2: .word 4

.text
.global main

main:

    push {ip, lr}

    // load scanf arguments and call scanf
    ldr    r1, =num_1
    ldr    r0, =int_format
    bl     scanf
    // load scanf arguments and call scanf
    ldr    r1, =num_2
    ldr    r0, =int_format
    bl     scanf
    // load first number by adress
    ldr    r1, =num_1
    ldr    r1, [r1]

    mov    r3, r1
    // load second number
    ldr    r1, =num_2
    ldr    r1, [r1]
    // calc result
    add    r3, r1
    // call printf
    ldr    r0, =int_format
    mov    r1, r3
    bl     printf

    pop {ip, pc}

    bx lr
