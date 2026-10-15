#include "types.h"
s32 MenuEquipCacheSet_29fa00(u8 *p, s32 i, s32 j, s32 v)
{
    s32  t;
    s32 *q;

    t = i * 16;
    q = (s32 *)(j * 4 + (t + (s32)p));
    q[0x1B] = v;
    return 1;
}
