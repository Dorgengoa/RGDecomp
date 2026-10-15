#include "types.h"
#pragma opt_loop_invariants off

extern "C" {
static inline s16 *get(u8 *t, s32 i)
{
    bool ok;
    ok = 0;
    if (i >= 0 && i < *(s16 *)(t + 0x7C)) {
        ok = 1;
    }
    if (!ok) {
        return 0;
    }
    return (s16 *)(*(u8 **)(t + 0x8C) + i * 8);
}

s16 *WorldSubsysFindRowByKey_3f64e0(void *arg0, s64 arg1) {
    s16 *p;
    s32 i;
    u8 *temp_6;
    s32 key;

    temp_6 = *(u8 **)((u8 *)arg0 + 0x10);
    if (temp_6 == 0) {
        return 0;
    }
    key = (s16)arg1;
    for (i = 0; ; i++) {
        p = get(temp_6, i);
        if (p == 0) {
            break;
        }
        if (*p == key) {
            return p;
        }
    }
    return 0;
}
}
