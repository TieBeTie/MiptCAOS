.intel_syntax noprefix
.global _start
_start:

   mov eax, 4
   mov ebx, 1
   lea ecx, hello
   mov edx, 12
   int 0x80

   mov eax, 1
   mov ebx, 0
   int 0x80

hello:
   .string "Hello, world"
hello_ptr:
   .long hello

