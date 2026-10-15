#include "types.h"

extern void EffectEntryGetPosByIdx_2de080(u8 *p);

s32 EffectGetPos_2e08c0(u8 *a0, s16 *p)
{
    s32 v;

    v = *p;
    if (v == 1) {
        goto out;
    }
    if (v == 2) {
        goto call;
    }
    if (v != 3) {
        goto out;
    }
call:
    EffectEntryGetPosByIdx_2de080(a0 + 0x1674);
out:
    return 0;
}
