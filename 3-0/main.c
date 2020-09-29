#include <stdio.h>
#include <stdint.h>

uint32_t A = 5;
uint32_t B = 3;
uint32_t C = 1;
uint32_t D = 8;

extern uint32_t R;

extern
void calculate ();

int main () {
    calculate();
    printf("%d", R);
    return 0;
}
