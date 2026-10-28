/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryIntList_3fe4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E3fe4b0 {
    u8 pad0[0x48];
    s16 unk48;
    u8 pad4A[2];
    s32 unk4C;
    s16 unk50;
    u8 pad52[2];
    s16 *unk54;
} E3fe4b0;

typedef struct T3fe4b0 {
    u8 pad0[0x6C];
    u8 unk6C[0x10];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    E3fe4b0 *unk8C;
} T3fe4b0;

extern T3fe4b0 *D_004830F8;
extern s16 D_004830FC;
/*rgp*/
/*rgp*/

s32 DataTableCmdEntryIntList_3fe4b0(s64 *arg0)
{
    T3fe4b0 *t;
    E3fe4b0 *e;
    s32 idx;
    s32 i;

    t = D_004830F8;
    if (t->unk7C <= 0) {
        return 1;
    }
    idx = D_004830FC - 1;
    if (idx >= t->unk7C) {
        return 1;
    }
    e = &t->unk8C[idx];
    e->unk50 = VariantGetInt_15f780(arg0++);
    if (e->unk50 > 0) {
        e->unk54 = ((s16 *)ArenaNew_3ff030(e->unk48 * 2, t->unk6C, 4, -1));
    } else {
        e->unk54 = 0;
    }
    if (e->unk4C != 0) {
        for (i = 0; i < e->unk50; i++) {
            e->unk54[i] = VariantGetInt_15f780(arg0++);
        }
    }
    return 1;
}
