#include <stdint.h>
#include <stdio.h>

uint32_t gray_code(uint32_t n) {
    return (n ^ (n >> 1));
}

void make_test() {
    for (int i = 0; i < 20; i++)
        printf("(%u) = %u\n", i, gray_code(i));
}

int main() {
    make_test();
    return (0);
}
