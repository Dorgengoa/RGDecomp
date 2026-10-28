/* rgp:protos */
#define RGP_SELF_DataTableCmdRevelationBoardSetCellKind_4086d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 b0;
    u8 lo : 1;
    u8 f : 4;
    u8 hi : 3;
    u8 b2;
    u8 b3;
} Cell004086d0;

typedef struct {
    u8 pad0[4];
    Cell004086d0 c[0x1D4];
} Tbl004086d0;

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    u8 *unk8C;
} Obj004086d0;

/*rgp*/
extern Obj004086d0 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdRevelationBoardSetCellKind_4086d0(s64 *arg0)
{
    s32 idx;
    s32 v;
    s32 n;
    s32 i;
    s32 t;
    Tbl004086d0 *tbl;
    Cell004086d0 *c;

    if (D_004830F8->unk7C <= 0) {
        return 1;
    }
    idx = D_004830FC - 1;
    if (idx >= D_004830F8->unk7C) {
        return 1;
    }
    tbl = (Tbl004086d0 *)(D_004830F8->unk8C + idx * 0x754);
    t = VariantGetInt_15f780(arg0++);
    n = VariantGetInt_15f780(arg0++);
    for (i = 0; i < n; i++) {
        v = VariantGetInt_15f780(arg0++);
        v = (v % 24 + 1) + (v / 24 + 1) * 26;
        if (v < 0 || v >= 0x1D4) {
            continue;
        }
        c = &tbl->c[v];
        switch (t) {
        case 0:
            c->f = 1;
            break;
        case 1:
            c->f = 3;
            break;
        case 2:
            c->f = 4;
            break;
        case 3:
            c->f = 2;
            break;
        }
    }
    return 1;
}
