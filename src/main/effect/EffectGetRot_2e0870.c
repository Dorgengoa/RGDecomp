#include "types.h"

extern void EffectEntryGetRotByIdx_2de030(u8 *p);

s32 EffectGetRot_2e0870(u8 *a0, s16 *p)
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
    EffectEntryGetRotByIdx_2de030(a0 + 0x1674);
out:
    return 0;
}
