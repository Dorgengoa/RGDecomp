#include "types.h"
#pragma opt_propagation off
typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    s32 unk4;
    s32 unk8;
} R;

typedef struct {
    s16 unk0;
    s16 unk2;
    R *unk4;
} E;

typedef struct {
    u8 pad0[0x6C];
    u8 unk6C[0x10];
    s16 unk7C;
    u8 pad7E[2];
    s16 unk80;
    u8 pad82[0x8C - 0x82];
    E *unk8C;
} T;

extern u8 VariantGetInt_15f780(s32, s32, E *);
extern s32 ArenaNew_407f50(s32, void *, s16, s32);
extern T *D_004830F8;
extern s16 D_004830FC;
extern u8 D_00483C78;
extern s8 D_00483C7C;

s32 DataTableCmdAllocSubEntries_4074d0(s32 arg0)
{
    T *t;
    s16 n;
    s32 idx;
    E *e;
    R *r;
    s32 m;

    t = D_004830F8;
    n = t->unk7C;
    if (n <= 0) {
        return 1;
    }
    idx = D_004830FC - 1;
    if (idx >= n) {
        return 1;
    }
    e = &t->unk8C[idx];
    if (D_00483C78 - 1 >= e->unk2) {
        return 1;
    }
    r = e->unk4 + D_00483C78 - 1;
    r->unk1 = VariantGetInt_15f780(arg0, D_00483C78, e);
    if (r->unk1 > 0) {
        m = ArenaNew_407f50(r->unk1 * 6, t->unk6C, t->unk80, -1);
        r->unk4 = m;
        if (m == 0) {
            return 1;
        }
    }
    D_00483C7C = 0;
    return 1;
}
