#include "types.h"

typedef struct {
    u8 pad0[0xa];
    s16 unkA;
    u8 padC[0x2];
    s16 unkE;
    u8 pad10[0x2];
    s16 unk12;
    u8 pad14[0x2];
    s16 unk16;
} T37B500_arg0;

u8 SaveSlotListPageScrollMaybe_37b500(T37B500_arg0 *arg0, s32 arg1)
{
    s32 t12;
    s32 t16;
    s32 a;
    s16 n;
    s32 m;

    t16 = arg0->unk16;
    t12 = arg0->unk12;
    if (arg1 != 0) {
        a = arg0->unkA + 1;
        if (t16 <= arg0->unkE - a) {
            arg0->unk16 = t16 + (s16)a;
            a = arg0->unkA;
            m = arg0->unkE - a;
            if (m < arg0->unk16) {
                arg0->unk16 = m;
            }
        } else if (t12 < arg0->unkA) {
            arg0->unk12 = arg0->unkA;
        }
    } else if (t16 > 0) {
        n = t16 - 3;
        arg0->unk16 = n;
        if (n < 0) {
            arg0->unk16 = 0;
        }
    } else if (t12 > 0) {
        arg0->unk12 = 0;
    }
    return t16 != arg0->unk16 || t12 != arg0->unk12;
}
