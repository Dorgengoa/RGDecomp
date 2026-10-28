/* rgp:protos */
#define RGP_SELF_NameTableAllocArrays_15a3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xC];
    s32 unk1C;
    u8 pad20[0x1A4];
    u8 *unk1C4;
    s32 *unk1C8;
    s32 unk1CC;
    s32 unk1D0;
    u8 *unk1D4;
    s32 *unk1D8;
    s32 unk1DC;
    s32 unk1E0;
} T15a3b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

#pragma opt_propagation off
void NameTableAllocArrays_15a3b0(T15a3b0 *arg0, s32 arg1, u32 arg2, s32 arg3)
{
    s32 v;
    u32 n;
    u32 k;
    s32 i;

    n = arg2;
    arg0->unkC = arg2;
    v = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(arg2 * 0x10 + 0x10, arg3)), NameTableEntryCtorMaybe_15a590, 0, 0x10, n));
    arg0->unk1C = v;
    if (v == 0) {
        arg0->unkC = 0;
    }
    arg0->unk1CC = arg1;
    arg0->unk1C4 = (u8 *)((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(arg1 * 0x68 + 0x10, arg3)), NameTableNodeCtor_15ae50, 0, 0x68, arg1));
    n = arg0->unk1CC * 4;
    if (!(n & 0xF)) {
        k = n >> 4;
    } else {
        k = (n >> 4) + 1;
    }
    arg0->unk1C8 = ((s32 *)MemStackAllocQw_14d950(arg3, k));
    for (i = 0; i < arg0->unk1CC; i++) {
        arg0->unk1C8[i] = (s32)(arg0->unk1C4 + i * 0x68);
    }
    arg0->unk1D0 = 0;
    arg0->unk1DC = arg1;
    arg0->unk1D4 = (u8 *)((s32)MemStackNew_14e1b0(arg1 * 8, arg3));
    n = arg0->unk1DC * 4;
    if (!(n & 0xF)) {
        k = n >> 4;
    } else {
        k = (n >> 4) + 1;
    }
    arg0->unk1D8 = ((s32 *)MemStackAllocQw_14d950(arg3, k));
    for (i = 0; i < arg0->unk1DC; i++) {
        arg0->unk1D8[i] = (s32)(arg0->unk1D4 + i * 8);
    }
    arg0->unk1E0 = 0;
}
