/* rgp:protos */
#define RGP_SELF_InvDiscardItem_3c5010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
        r = ((s32)PartyFindItemHolder_3d4c20(arg1)) != 0;
        if (r) {
            return 0;
        }
    }
    ItemMarkRemoved_3d4130(arg1, arg2);
    PoolFreeElemByPtr_36aa80(*(s32 *)((u8 *)arg0 + 0x168), arg1);
    return 1;
}
