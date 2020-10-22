#include <asm/unistd_32.h>
    .intel_syntax noprefix
    .text
    .global _start
_start:

     lea eax, exit1
     push eax

     mov eax, 4
     mov ebx, 1
     mov ecx, hello_world_ptr
     mov edx, 13

     lea ebp, [esp - 12]
     sysenter
     exit1:

     lea eax, exit2
     push eax
     push ecx
     push edx
     push ebp
     mov eax, 1
     mov ebx, 0
     mov ebp, esp
     sysenter
     exit2:

hello_world:
     .asciz "Hello, World!"

hello_world_ptr:
     .long hello_world
