#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

extern float_class_t classify(double *value_ptr) {
    void * x = value_ptr;
    unsigned long long* y = x;
    unsigned long long number = *y;
    printf("%.3lf\n", *value_ptr);
    unsigned long long n = number; 

while (n) {
    if (n & 1)
        printf("1");
    else
        printf("0");

    n >>= 1;
}
printf("\n");  

    if (number == 0) {
       return PlusZero;
    }
    if (number == (1ull << 63)) {
       return MinusZero;
    }
    if (number == 4095ull << 52) {
       return MinusInf;
    }
    if (number == (2047ull << 52)) {
       return PlusInf;
    }
    if ((number & (2047ull << 52)) == ( 2047ull << 52)) {
       if ((number << 13) == 0) {
         return QuietNaN;
	   } else {
	     return SignalingNaN;
	   }
    }
    if ((number & (1ull << 63)) == (1ull << 63) && ((number << 1) & (2046ull << 53)) == 0 && (number << 12) != 0) {
      return MinusDenormal;
    }
    if ((number & (2047ull << 52)) == 0 && (number << 12) != 0) {
       return PlusDenormal;
    }
    if (*value_ptr > 0) {
      return PlusRegular;
    } else {
      return MinusRegular;
    }
}

int main () {
  double x = 0; 
printf("\n%lf\t%x", x, classify(&x)); 
long long i = 0x8000000000000000; 
double* px = &i; 
printf("\n%lf\t%x", *px, classify(px)); 
i = 0x7FF0000000000000; 
px = &i; 
printf("\n%lf\t%x", *px, classify(px)); 
i = 0xFFF0000000000000; 
px = &i; 
printf("\n%lf\t%x", *px, classify(px)); 
x = 1; 
printf("\n%lf\t%x", x, classify(&x)); 
x = -1; 
printf("\n%lf\t%x", x, classify(&x)); 
i = 0x000000000000000F; 
px = &i; 
printf("\n%lf\t%x", *px, classify(px)); 
i = 0x800000000000000F; 
px = &i; 
printf("\n%lf\t%x", *px, classify(px)); 
i = 0x7FFFFFFFFFFFFFFF; 
px = &i; 
printf("\n%lf\t%x", *px, classify(px)); 
x = 0; 
x = 0 / x; 
printf("\n%lf\t%x", x, classify(&x));
  return 0;
}

