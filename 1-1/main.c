#include <stdint.h>

uint16_t satsum(uint16_t x, uint16_t y) {
  int16_t t = -1;
  uint16_t max = t;
  if (x >= max - y) {
    return max;
  } else {
    return x + y;
  }
}
