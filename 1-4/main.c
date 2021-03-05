#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern int check_int(uint32_t u32) {
    while ((u32 != 0) && (u32 & 1) == 0) {
        u32 >>= 1;
    }
    return (u32 >> 24) == 0;
}

int main () {
   uint32_t u32 = (1 << 24) + 1;
   check_int(u32);
   printf("%d", check_int(u32)); 
   
}
