#include "types.h"
#pragma opt_common_subs off

typedef struct T00151220 {
    s32 unk0;
    s8 ***unk4;
} T00151220;

typedef struct P00151220 {
    u8 pad0[0x104];
    T00151220 *unk104;
} P00151220;

static inline bool streq(s8 *a, s8 *b)
{
    s8 c;
    if (*a != *b) {
        return false;
    }
    while ((c = *a) != 0 || *b != 0) {
        if (c != *b) {
            return false;
        }
        a++;
        b++;
    }
    return true;
}

extern "C" s32 ModelFindFrameIndexByName_151220(P00151220 *arg0, s8 *arg1)
{
    T00151220 *t;
    s32 i;
    s8 **e;
    s8 *s;

    t = arg0->unk104;
    if (arg1 == NULL || t == NULL) {
        return -1;
    }
    for (i = 0; i < t->unk0; i++) {
        e = t->unk4[i];
        if (e == NULL) {
            continue;
        }
        s = *e;
        if (s == NULL) {
            continue;
        }
        if (streq(s, arg1)) {
            return i;
        }
    }
    return -1;
}
