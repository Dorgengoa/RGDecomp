#include "types.h"

static inline s32 get(void *t, s32 idx)
{
    s32 ok;
    ok = 0;
    if (idx >= 0 && idx < *(s16 *)((u8 *)t + 0x7C)) {
        ok = 1;
    }
    if (!ok) {
        return 0;
    }
    return *(s32 *)((u8 *)t + 0x8C) + (idx * 0x3C);
}

s32 RowRangeIterGetAt_40f290(void *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 idx;
    void *t;

    t = *(void **)((u8 *)arg0 + 0x4);
    if (t == NULL) {
        return 0;
    }
    a = *(s16 *)((u8 *)arg0 + 0x8);
    if (a < 0 || (b = *(s16 *)((u8 *)arg0 + 0xA)) < 0) {
        return 0;
    }
    idx = a + arg1;
    if (b < idx) {
        return 0;
    }
    return get(t, idx);
}
