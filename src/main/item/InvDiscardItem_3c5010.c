#include "types.h"
#pragma opt_common_subs off

extern void PoolFreeElemByPtr_36aa80(s32, s32);
extern void ItemMarkRemoved_3d4130(s32, s32);
extern s32 ItemIsUnheldFlaggedMaybe_3d4420(s32);
extern s32 PartyFindItemHolder_3d4c20(s32);

s32 InvDiscardItem_3c5010(void *arg0, s32 arg1, s32 arg2)
{
    s32 r;

    if (arg1 == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x168) == 0) {
        return 0;
    }
    if (arg2 == 0) {
        if (ItemIsUnheldFlaggedMaybe_3d4420(arg1) == 0) {
            return 0;
        }
        r = PartyFindItemHolder_3d4c20(arg1) != 0;
        if (r) {
            return 0;
        }
    }
    ItemMarkRemoved_3d4130(arg1, arg2);
    PoolFreeElemByPtr_36aa80(*(s32 *)((u8 *)arg0 + 0x168), arg1);
    return 1;
}
