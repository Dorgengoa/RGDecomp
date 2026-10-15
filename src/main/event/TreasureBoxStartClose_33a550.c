#include "types.h"

extern const f32 D_0047DD38 __attribute__((section(".sdata")));

typedef struct Obj {
    u8 pad0[0x26];
    s16 unk26;
    s16 unk28;
    u8 pad2A[0x5C - 0x2A];
    f32 unk5C;
    u8 pad60[0x70 - 0x60];
    u8 b0 : 5;
    u8 b5 : 1;
    u8 b6 : 2;
} Obj;

s32 TreasureBoxStartClose_33a550(Obj *arg0) {
    s16 st;

    st = arg0->unk26;
    if ((st & 3) != 0 && (st & 3) != 1) {
        return 0;
    }
    arg0->unk26 = (st & ~3) | 2;
    arg0->unk28 = 0;
    arg0->unk5C = D_0047DD38;
    arg0->b5 = 0;
    return 1;
}
