    .intel_syntax noprefix
    .text
    .global _start
_start:

     loop:

         mov eax, 3
         mov ebx, 2
         mov ecx, byte_ptr
         mov edx, 1
         int 0x80
         cmp eax, 0
         je end
         mov eax, 4
         mov ebx, 1
         mov ecx, byte_ptr
         mov edx, 1
         int 0x80

         jmp loop

     end:
     mov eax, 1
     mov ebx, 0
     int 0x80
.data
my_byte:
     .byte 0
byte_ptr:
     .long my_byte

