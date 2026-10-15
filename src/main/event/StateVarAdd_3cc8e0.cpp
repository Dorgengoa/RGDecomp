#include "types.h"

extern "C" bool StateVarSet_3cc9c0(u8 *base, s32 i, s16 v, s32 z);

extern "C" s32 StateVarAdd_3cc8e0(u8 *base, s32 i, s32 v)
{
    s16 h;
    s32 off;

    if (i < 0) goto fail;
    if (i < 0x80) goto ok;
fail:
    return -1;
ok:
    off = i * 2;
    h = *(s16 *)(off + (s32)base + 0x128);
    return StateVarSet_3cc9c0(base, i, (s16)(h + (s16)v), 0);
}
