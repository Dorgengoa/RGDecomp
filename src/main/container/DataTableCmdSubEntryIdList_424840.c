#include "types.h"

typedef struct Ent {
    u64 lo : 49;
    u64 cnt : 7;
    u64 hi : 8;
    s16 *x8;
} Ent;

typedef struct Grp {
    u8 pad0[0xA];
    s16 xA;
    Ent *xC;
} Grp;

typedef struct Top {
    u8 pad0[0x6C];
    u8 x6C[0x10];
    s16 x7C;
    u8 pad7E[0xE];
    Grp *x8C;
} Top;

extern s32 VariantGetInt_15f780(s64 *arg0);
extern s16 *ArenaNew_424f40(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern Top *D_004830F8;
extern s16 D_004830FC;
extern s32 D_00483F10;
extern u8 D_00483F14;

s32 DataTableCmdSubEntryIdList_424840(s64 *arg0)
{
    Top *t;
    Grp *g;
    Ent *e;
    s16 *p;
    s32 i;
    u8 n;

    t = D_004830F8;
    if (D_00483F14 != 0) {
        return 1;
    }
    if (t->x7C <= 0) {
        return 1;
    }
    if (!(D_004830FC - 1 < t->x7C)) {
        return 1;
    }
    g = &t->x8C[D_004830FC - 1];
    if (g->xC == 0) {
        return 1;
    }
    if (g->xA <= 0) {
        return 1;
    }
    if (!(D_00483F10 - 1 < g->xA)) {
        return 1;
    }
    e = (Ent *)((u8 *)g->xC + D_00483F10 * 12 - 12);
    e->cnt = VariantGetInt_15f780(arg0++);
    n = (u8)(e->cnt & 0xFF);
    if (n > 0) {
        e->x8 = ArenaNew_424f40(n * 2, t->x6C, 4, -1);
    } else {
        e->x8 = 0;
    }
    p = e->x8;
    if (p != 0) {
        for (i = 0; i < e->cnt; i++) {
            *p++ = VariantGetInt_15f780(arg0++);
        }
    }
    return 1;
}
