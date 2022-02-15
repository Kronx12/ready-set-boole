#include <stdint.h>
#include <stdio.h>

uint32_t adder(uint32_t a, uint32_t b) {
    uint32_t carry = (a & b) << 1;
    uint32_t sum = a ^ b;

    while (carry > 0) {
        carry = (a & b) << 1;
        sum = a ^ b;
        a = carry;
        b = sum;
    }
    return (sum);
}

uint32_t multiplier(uint32_t a, uint32_t b) {
    uint32_t res = 0;

    uint32_t min = a < b ? a : b;
    uint32_t max = a > b ? a : b;

    for (uint32_t i = 0; i < min; i++)
        res = adder(res, max);
    return (res);
}

void make_test(uint32_t a, uint32_t b) {
    printf("%s %u * %u = %u(%u)\033[0m\n", multiplier(a, b) == a * b ? "\033[1;34m" : "\033[1;35m", a, b, multiplier(a, b), a * b);
}

int main() {
    make_test(0, 0);
    make_test(0, 1);
    make_test(1, 0);
    make_test(1, 1);
    make_test(3, 7);
    make_test(10, 10);
    make_test(25, 25);
    make_test(12345, 12345);
    make_test(4294967295, 0);
    return (0);
}
