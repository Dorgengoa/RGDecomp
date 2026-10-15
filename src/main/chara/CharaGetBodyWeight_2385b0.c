#include "types.h"

f32 CharaGetBodyWeight_2385b0(void *p)
{
    void *q;
    f32 v;

    q = *(void **)((s32)p + 0x3F4);
    if (q != 0) {
        v = *(f32 *)((s32)q + 0x4D0);
    } else {
        v = 0.0f;
    }
    return v > 30.0f ? v : 30.0f;
}
