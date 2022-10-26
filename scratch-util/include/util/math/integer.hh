
#ifndef __HH_UTIL_MATH_INTEGER_
#define __HH_UTIL_MATH_INTEGER_

#include <climits>
#include <bit>

namespace util::math
{

    template <typename uint_t> auto log2i(uint_t x) -> uint_t
    {
        return sizeof(x) * CHAR_BIT - std::countl_zero(x) - 1;
    }

    template <typename uint_t> auto isqrt(uint_t x) -> uint_t
    {
        uint_t x_last = 0, x_curr = 0x1 << (log2i(x) >> 1);
        while (x_curr != x_last)
        {
            x_last = x_curr;
            x_curr = (x_curr * x_curr > x)
                ? x_curr - (x_curr * x_curr - x) / (2 * x_curr)
                : x_curr + (x - x_curr * x_curr) / (2 * x_curr);
        }
        return x_curr;
    }

} // namespace util::math

#endif /* __HH_UTIL_MATH_INTEGER_ */
