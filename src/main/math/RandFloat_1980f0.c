#include "types.h"

f32 RandFloat_1980f0(u32 *p)
{
    u32 x;

    x = *p * 0x5D588B65 + 1;
    *p = x;
    return 2.3283064365386963e-10f * (f32)x;
}
