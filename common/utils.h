#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <cstdint>

/**
 * Shifts a number left, reintroducing overflown bits on the right.
 */
inline uint32_t rotl32(uint32_t x, uint32_t y)
{
    return (x << y | x >> (32-y)) & 0xFFFFFFFF;
}

/**
 * Integer module which "rounds down" even on negative integers.
 *
 * Given a and n, this returns 0 <= p < b so that a = k * n + p with k integer.
 */
inline int mod(int a, int n)
{
    if(a >= 0)
        return a % n;
    else
        return n - 1 - (-a - 1) % n;
}

#endif
