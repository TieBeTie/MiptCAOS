#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned long long ZERO = 0ull;
const unsigned long long ONE = 1ull;
const unsigned long long TWELVE = 12ull;
const unsigned long long THIRTEEN = 13ull;
const unsigned long long FIFTY_TWO = 52ull;
const unsigned long long FIFTY_THREE = 53ull;
const unsigned long long SIXTY_THREE = 63ull;
const unsigned long long TWENTY_FORTY_SIX = 2046ull;
const unsigned long long TWENTY_FORTY_SEVEN = 2047ull;
const unsigned long long FOURTY_NINGTY_FIVE = 4095ull;

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
    if (number == ZERO) {
       return PlusZero;
    }
    if (number == (ONE << SIXTY_THREE)) {
       return MinusZero;
    }
    if (number == FOURTY_NINGTY_FIVE << FIFTY_TWO) {
       return MinusInf;
    }
    if (number == (TWENTY_FORTY_SEVEN << FIFTY_TWO)) {
       return PlusInf;
    }
    if ((number & (TWENTY_FORTY_SEVEN << FIFTY_TWO)) == (TWENTY_FORTY_SEVEN << FIFTY_TWO)) {
       if ((number << THIRTEEN) == ZERO) {
         return QuietNaN;
	   } else {
	     return SignalingNaN;
	   }
    }
    if ((number & (ONE << SIXTY_THREE)) == (ONE << SIXTY_THREE) && ((number << ONE) & (TWENTY_FORTY_SIX << FIFTY_THREE)) == ZERO && (number << TWELVE) != ZERO) {
      return MinusDenormal;
    }
    if ((number & (TWENTY_FORTY_SEVEN << FIFTY_TWO)) == ZERO && (number << TWELVE) != ZERO) {
       return PlusDenormal;
    }
    if (*value_ptr > ZERO) {
      return PlusRegular;
    } else {
      return MinusRegular;
    }
}
