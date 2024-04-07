#include <stdio.h>

/* Assume 32-bit architecture */
#define BITS_PER_LONG 32

/**
 * __fls - find last (most-significant) set bit in a long word
 * @word: the word to search
 *
 * Undefined if no set bit exists, so code should check against 0 first.
 */
static inline unsigned long __fls(unsigned long word)
{
	int num = BITS_PER_LONG - 1;

#if BITS_PER_LONG == 64
	if (!(word & (~0ul << 32))) {
		num -= 32;
		word <<= 32;
	}
#endif
	if (!(word & (~0ul << (BITS_PER_LONG-16)))) {
		num -= 16;
		word <<= 16;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-8)))) {
		num -= 8;
		word <<= 8;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-4)))) {
		num -= 4;
		word <<= 4;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-2)))) {
		num -= 2;
		word <<= 2;
	}
	if (!(word & (~0ul << (BITS_PER_LONG-1))))
		num -= 1;
	return num;
}

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
    printf("%lu\n", __fls(N));
    return 0;
}