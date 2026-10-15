#include "types.h"
#pragma optimization_level 3

static inline bool streq173a00(s8 *p, s8 *q)
{
    s8 c;

    if (*p != *q) {
        return false;
    }
    while ((c = *p) != 0 || *q != 0) {
        if (c != *q) {
            return false;
        }
        p++;
        q++;
    }
    return true;
}

extern "C" s32 NamedRecFindIndex_173a00(void *arg0, s8 *arg1)
{
    s32 i;
    s32 base;

    if (arg1 == NULL) {
        return -1;
    }
    base = *(s32 *)((u8 *)arg0 + 0x8);
    if (base == 0) {
        return 0;
    }
    for (i = 0; i < *(s32 *)((u8 *)arg0 + 0x4); i++) {
        if (streq173a00((s8 *)(base + i * 0x30), arg1)) {
            return i;
        }
    }
    return -1;
}
