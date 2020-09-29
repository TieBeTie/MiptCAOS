#include <stdint.h>

extern int check_int(uint32_t u32) {
    while ((u32 != 0) && (u32 & 1) == 0) {
        u32 >>= 1;
    }
    return (u32 >> 24) == 0;
}
