#include "types.h"

#pragma divbyzerocheck on

typedef struct Ent_FUN_00434d30 {
    u8 pad000[0x14];
    s16 f14;
    s16 f16;
} Ent_FUN_00434d30;

typedef struct Obj_FUN_00434d30 {
    u8 pad000[0x4];
    s32 f04;
    u8 pad008[0x20];
    s16 f28;
    s16 f2A;
    u8 pad02C[0xBC];
    s8 fE8[1];
} Obj_FUN_00434d30;

extern Ent_FUN_00434d30 *UiEntryListFindByTag_28ea40(s32 h, s32 k);

void TextEntryCursorToCommitKey_434d30(Obj_FUN_00434d30 *o)
{
    Ent_FUN_00434d30 *e;
    s32 i;

    e = UiEntryListFindByTag_28ea40(o->f04, 0x6D61);
    for (i = 0; i < 0x57; i++) {
        if (o->fE8[i] == 0x43) {
            e->f14 = i % 0x1D;
            o->f28 = i % 0x1D;
            e->f16 = i / 0x1D;
            o->f2A = i / 0x1D;
            return;
        }
    }
}
