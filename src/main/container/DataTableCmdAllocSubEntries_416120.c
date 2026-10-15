#pragma opt_propagation off
#include "types.h"

/* s44g clone pair (DataTableCmdAllocSubEntries_3f47a0 / DataTableCmdAllocSubEntries_416120).  MATCH (s41 agent36):
   `n * 0x14` spelled on `ret` + `#pragma opt_propagation off`. */

typedef struct Elem00416120 {
    u8 pad0[0x1C];
    s32 unk1C;
    s32 unk20;
    u8 pad24[0x28 - 0x24];
} Elem00416120;

typedef struct Ctx00416120 {
    u8 pad00[0x6C];
    u8 unk6C[0x10];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    Elem00416120 *unk8C;
    u8 pad90[0x94 - 0x90];
    s32 unk94;
} Ctx00416120;

extern Ctx00416120 *D_004830F8;
extern s16 D_004830FC;

extern s32 VariantGetInt_15f780(s32 vp);
extern s32 ArenaNew_4171a0(s32 size, void *pool, s32 align, s32 flag);
extern s32 ConstructNewArray_100710(s32 ptr, s32 a1, s32 a2, s32 size, s32 count);

/* arg0 flows straight through to VariantGetInt_15f780 and is otherwise unused --
   retail never writes $4 between function entry and that call. */
s32 DataTableCmdAllocSubEntries_416120(s32 arg0)
{
    Ctx00416120 *ctx;
    s16 count;
    s32 index;
    Elem00416120 *elem;
    s32 ret;
    u32 n;
    s32 sz;

    ctx = D_004830F8;
    count = ctx->unk7C;
    if (count <= 0) {
        return 1;
    }
    index = D_004830FC - 1;
    if (index >= count) {
        return 1;
    }
    elem = ctx->unk8C + index;
    ret = VariantGetInt_15f780(arg0);
    elem->unk1C = ret;
    if (ret > 0) {
        n = ret;
        elem->unk20 = ConstructNewArray_100710(ArenaNew_4171a0(ret * 0x14 + 0x10, ctx->unk6C, 4, -1), 0, 0, 0x14, n);
    } else {
        elem->unk20 = 0;
    }
    ctx->unk94 = 0;
    return 1;
}
