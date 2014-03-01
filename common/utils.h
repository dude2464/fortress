#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <cstdint>

inline uint32_t shift32(uint32_t x, uint32_t y)
{
    return (x << y | x >> (32-y)) & 0xFFFFFFFF;
}

inline unsigned int bits(unsigned int n)
{
    return (1 << n) - 1;
}

inline int mod(int a, int b)
{
    return
    (a >= 0)?
        (a % b)
    :
        (b - 1 - (-a - 1) % b);
}

#endif
