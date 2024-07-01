#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define frac_bits 16

unsigned long fixed_sqrt(unsigned long x)
{
    if (!x || x == (1U << frac_bits))
    return x;

    unsigned long z = 0;
    unsigned long m = 1UL << ((63 - __builtin_clzl(x)) & ~1UL);
    for (; m; m >>= 2) {
        unsigned long b = z + m;
        z >>= 1;
        if (x >= b) {
            x -= b;
            z += m;
        }
    }
    z <<= (frac_bits >> 1);
    return z;
}

double restore_double(unsigned long fixed_value) {
    return (double)fixed_value / (1 << frac_bits);
}

int main()
{

    unsigned long x = pow(2, 47) - pow(2, -16);
    
    double float_result = sqrt((double)x);
    unsigned long fixed_result = fixed_sqrt((unsigned long)(x * (1 << frac_bits)));
    double fixed_result_float = restore_double(fixed_result);

    printf("number = %ld, float result = %f, and fixed result = %f\n", x, float_result, fixed_result_float);

    return 0;
}
