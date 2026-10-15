#include "types.h"
f64 UIntToDouble_100320(u32 x)
{
    u64 y = x;
    f64 r;
    if ((s64)y > 0)
        return (f64)(s64)y;
    r = (f64)(s64)((y >> 1) | (y & 1));
    return r + r;
}
