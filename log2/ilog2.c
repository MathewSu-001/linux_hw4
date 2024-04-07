#include <stdio.h>

static size_t ilog2(size_t i)
{
    size_t result = 0;
    while (i >= 65536) {
        result += 16;
        i >>= 16;
    }
    while (i >= 256) {
        result += 8;
        i >>= 8;
    }
    while (i >= 16) {
        result += 4;
        i >>= 4;
    }
    while (i >= 2) {
        result += 1;
        i >>= 1;
    }
    return result;
}

int ilog32(size_t v)
{
    return (31 - __builtin_clz(v | 1));
}

int main()
{
    int N = 256;
    printf("%lu\n", ilog2(N));
    printf("%d\n", ilog32(N));
    return 0;
}