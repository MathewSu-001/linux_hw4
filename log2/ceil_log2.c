#include <stdio.h>
#include <stdint.h>

int ceil_ilog2(uint32_t x)
{
    uint32_t r, shift;

    x--; //x-1 
    r = (x > 0xFFFF) << 4;  //if x > 2^16 ,r = 16                                                                                                                                  
    x >>= r;
    shift = (x > 0xFF) << 3; //if x > 2^8 ,shift = 8
    x >>= shift;
    r |= shift; //r = r + shift
    shift = (x > 0xF) << 2; //if x > 2^4 ,shift = 4
    x >>= shift;
    r |= shift; //r = r + shift
    shift = (x > 0x3) << 1; //if x > 2^2 ,shift = 2
    x >>= shift;
    return (r | shift | x > 1) + 1;       
}

int main()
{
    uint32_t N = 33;
    printf("%d\n", ceil_ilog2(N));
    return 0;
}