#pragma opt_propagation off
#include "types.h"
#pragma divbyzerocheck on

typedef struct S198920 {
    u8 pad0[8];
    f32 m8;
    f32 mC;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
} S198920;

typedef struct R198920 {
    u8 pad0[4];
    u32 seed;
    u8 pad8[0x48];
    f32 m50;
    f32 m54;
} R198920;

void EffTexUvRandParamRandomize_198920(S198920 *arg0, R198920 *arg1)
{
    s32 n;
    f32 r;
    s32 idx;
    s32 m;

    n = arg0->m1C - arg0->m18;
    if (n <= 1) {
        arg1->m54 = 0.0f;
        arg1->m50 = 0.0f;
        return;
    }
    {
        f32 fn;
        f32 k;
        arg1->seed = arg1->seed * 0x5D588B65 + 1;
        fn = (f32)(n + 1);
        k = 2.3283064e-10f;
        r = fn * (k * (f32)arg1->seed);
    }
    if (r >= (f32)n) {
        m = n;
    } else {
        m = (s32)r;
    }
    idx = (arg0->m18 + m) % (arg0->m10 * arg0->m14);
    arg1->m50 = arg0->m8 * (f32)(idx % arg0->m10);
    arg1->m54 = -arg0->mC * (f32)(idx / arg0->m10);
}
