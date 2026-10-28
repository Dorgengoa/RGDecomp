#include "types.h"
typedef unsigned _BitInt(128) __attribute__((aligned(16))) u128;

extern void PushApart_402080(f32 *p, u128 v, f32 a, f32 b);

void PushUser_4020a0(f32 *p)
{
    u128 v = 0;

    PushApart_402080(p, v, 2.0f, 3.0f);
}
