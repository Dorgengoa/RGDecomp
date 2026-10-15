#pragma opt_propagation off
#include "types.h"

typedef struct Item003928d0 {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 pad1C[4];
} Item003928d0;

typedef struct S003928d0 {
    u8 pad0[0x20];
    Item003928d0 *unk20;
} S003928d0;

extern s16 D_00464140[][5];
extern s16 D_00464160[][5];

void UiIconSetUvByKindMaybe_3928d0(void *arg0, S003928d0 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    Item003928d0 *p;
    Item003928d0 *e;
    s16 z;
    s16 a;
    s16 b;

    if (arg1 == NULL || arg4 < 0 || arg4 >= 5) {
        return;
    }
    p = arg1->unk20;
    if (p == NULL) {
        return;
    }
    e = &p[arg4];
    if (e == NULL) {
        return;
    }
    e->unk10 = e->unk14 = e->unk18 = e->unk1A = 0;
    if (arg3 >= 4) {
        e->unk8 = e->unkA = 0;
        e->unk4 = e->unkC = 0;
        e->unk6 = e->unkE = 0;
    } else {
        a = D_00464140[arg2][arg3];
        b = D_00464160[arg2][arg3];
        e->unk8 = a;
        e->unkA = b;
        e->unkC = 0x18;
        e->unk4 = 0x18;
        e->unkE = 0x18;
        e->unk6 = 0x18;
    }
}
