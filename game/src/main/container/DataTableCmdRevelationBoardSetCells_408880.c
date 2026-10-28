/* rgp:protos */
#define RGP_SELF_DataTableCmdRevelationBoardSetCells_408880 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
typedef struct E {
    __extension__ unsigned int a : 6;
    unsigned int b : 3;
    unsigned int c : 4;
    unsigned int pad : 19;
} __attribute__((aligned(4))) E;

typedef struct Blk {
    s32 hdr;
    E cells[0x1D4];
} Blk;

typedef struct Mgr {
    u8 pad0[0x7C];
    s16 cnt;
    u8 pad7E[0x8C - 0x7E];
    Blk *blocks;
} Mgr;

/*rgp*/
extern s32 D_00480234;
extern Mgr *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdRevelationBoardSetCells_408880(s64 *arg0)
{
    s32 cnt;
    s32 idx;
    s32 n;
    Blk *base;
    s32 i;
    s32 v16;
    s32 v2;
    s32 div;
    s32 mod;
    s32 combined;
    E *e;

    cnt = D_004830F8->cnt;
    if (cnt <= 0) {
        return 1;
    }
    idx = D_004830FC - 1;
    if (idx >= cnt) {
        return 1;
    }
    base = (Blk *)((u8 *)D_004830F8->blocks + idx * 0x754);
    n = VariantGetInt_15f780((s32)arg0++);
    for (i = 0; i < n; i++) {
        v16 = VariantGetInt_15f780((s32)arg0++);
        v2 = VariantGetInt_15f780((s32)arg0++);
        div = v2 / 24;
        mod = v2 % 24 + 1;
        combined = mod + (div + 1) * 0x1A;
        if (combined >= 0 && combined < 0x1D4) {
            e = &base->cells[combined];
            e->a = D_00480234;
            e->b = v16;
            e->c = 10;
        }
    }
    return 1;
}
