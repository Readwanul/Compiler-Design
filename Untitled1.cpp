#include <stdio.h>

int main() {
    unsigned int x = 29; // Binary: 11101, which has 4 set bits
    int count = __builtin_popcount(x);
    printf("Number of 1-bits in %u is %d\n", x, count);
    return 0;
}

