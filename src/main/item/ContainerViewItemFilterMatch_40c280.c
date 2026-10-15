#include "types.h"
#pragma opt_repositioncode off
typedef struct {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0x10 - 0x8];
    s32 unk10;
} Obj0Arg0Sub4;

typedef struct {
    u8 pad0[0x4];
    Obj0Arg0Sub4 *unk4;
    s16 unk8;
    s16 unkA;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
} Obj0Arg0;

typedef struct {
    u8 pad0[0x2];
    s8 unk2;
    s16 unk4;
    u8 pad6[0x1E - 0x6];
    s8 unk1E;
} Obj0Arg1;

extern s32 DoubleGreater_100260(s32, s32);
extern s32 ItemGroupUnlockTimeGet_3cbbb0(s32, s8);

s32 ContainerViewItemFilterMatch_40c280(Obj0Arg0 *arg0, Obj0Arg1 *arg1)
{
    s8 k;

    if (arg1 == NULL) {
        return 0;
    }
    if (arg0->unk8 >= 0 && arg1->unk2 != arg0->unk8) {
        return 0;
    }
    if (arg0->unkA >= 0 && arg1->unk4 != arg0->unkA) {
        return 0;
    }
    k = arg1->unk1E;
    if (k < 0) {
        if (arg0->b0) {
            goto ret1;
        }
        return 0;
    }
    if (!arg0->b1) {
        return 0;
    }
    if (DoubleGreater_100260(ItemGroupUnlockTimeGet_3cbbb0(arg0->unk4->unk10, k), 0) != 0) {
        if (arg0->b2) {
            goto ret1;
        }
        return 0;
    }
    if (arg0->b3) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}
