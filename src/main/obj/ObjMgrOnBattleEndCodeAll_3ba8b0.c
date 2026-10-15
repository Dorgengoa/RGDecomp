#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off
s32 PoolGetUsedElem_36acb0(s32, s32);
s32 ObjMgrGroupLetterSlotsReset_3bc270(u8 *);
s32 UnitOnBattleEndCode_3bcc90(s32, s32, s32, s32, s32);
extern s32 D_004659C8[0x100];

s32 ObjMgrOnBattleEndCodeAll_3ba8b0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 n;
    s32 i;
    s32 p;
    u8 *q;

    q = *(u8 **)(arg0 + 0x4);
    if (q == NULL) {
        return 0;
    }
    if (!(*(u8 *)(*(u8 **)(q + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x10) == 0) {
        return 0;
    }
    n = D_004659C8[0];
    for (i = 0; i < n; i++) {
        p = PoolGetUsedElem_36acb0(*(s32 *)(arg0 + 0x10), i);
        if (p != 0) {
            UnitOnBattleEndCode_3bcc90(p, arg1, arg2, arg3, arg4);
        }
    }
    ObjMgrGroupLetterSlotsReset_3bc270(arg0);
    return 1;
}
