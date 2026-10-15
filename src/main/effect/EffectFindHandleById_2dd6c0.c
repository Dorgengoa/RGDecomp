#include "types.h"

typedef struct R14 {
    s16 m0;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
} R14;

typedef struct Sub {
    s16 a;
    s16 b;
} Sub;

typedef struct Ent {
    u8 pad0[0xC];
    Sub s;
    u8 pad10[0xD0];
} Ent;

u8 *EffectEntryFindNodeByUid_2da0c0(u8 *, s32);

void EffectFindHandleById_2dd6c0(R14 *ret, u8 * arg1, s32 arg2) {
    s32 i;
    s16 k;
    u8 *t;
    s32 v;

    k = -1;
    for (i = 0; i < 0x30; i++) {
        if (((s16 *)(arg1 + i * 0xE0 + 0xC))[1] == -1) {
            continue;
        }
        t = EffectEntryFindNodeByUid_2da0c0(arg1 + i * 0xE0, arg2);
        if (t != 0) {
            v = *(s32 *)(t + 8);
            if (((s16 *)(arg1 + i * 0xE0 + 0xC))[0] == 0) {
                k = 2;
            } else if (((s16 *)(arg1 + i * 0xE0 + 0xC))[0] == 1) {
                k = 3;
            }
            ret->m0 = k;
            ret->m4 = arg2;
            ret->m8 = i;
            ret->mC = 0;
            ret->m10 = v;
            return;
        }
    }
    ret->m0 = -1;
    ret->m4 = -1;
    ret->m8 = -1;
    ret->mC = 0;
    ret->m10 = -1;
}
