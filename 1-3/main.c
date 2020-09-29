#include <stdio.h>
#include <stdint.h>

const uint64_t NUMBERS_COUNT = 10;
const uint64_t LETTERS_COUNT = 26;
const uint64_t EMPTY_SET = 0;
const uint64_t SET_SIZE = 62;
const uint64_t ONE = 1;

uint16_t get_bit_position (const char s) {
	
   if (s >= '0' && s <=  '9') {
      return s - '0';
   }
   
   if (s >= 'A' && s <= 'Z') {
      return NUMBERS_COUNT + s - 'A';
   }
   
   return NUMBERS_COUNT + LETTERS_COUNT + s - 'a';
   
}

void set_nth_bit (uint64_t* set, const uint64_t position) {
    *set |= (ONE << position);
}

char get_char_by_index (const uint64_t i) {
	
    if (i < NUMBERS_COUNT) {
        return '0' + i;
    }
    
    if (i >= NUMBERS_COUNT + LETTERS_COUNT) {
        return 'a' + i - NUMBERS_COUNT - LETTERS_COUNT;
    }
    
    return 'A' + i - NUMBERS_COUNT;
    
}

void print_result (const uint64_t result) {
	
    uint64_t mask = ONE;
    
    for (uint64_t i = 0; i < SET_SIZE; ++i) {
        if ((result & mask) == mask) {
	    printf("%c", get_char_by_index(i));
        }
        mask <<= ONE;
    }
    
}

void calc (uint64_t* result) {
	
    char s;
    uint64_t current = EMPTY_SET;
    
    while (scanf("%c", &s) != EOF) {
        if (s == '&') {
            *result &= current;
            current = EMPTY_SET;
        } else if (s == '|') {
            *result |= current;
            current = EMPTY_SET;
        } else if (s == '^') {
            *result ^= current;
            current = EMPTY_SET;
        } else if (s == '~') {
            *result = ~*result;
            current = EMPTY_SET;
        } else {
            set_nth_bit(&current, get_bit_position(s));
        }
   }
   
}

int main () {
	
    uint64_t result = EMPTY_SET;
    
    calc(&result);
    
    print_result(result);
    
    return 0;
}
