/* rgp:protos */
#define RGP_SELF_CharaResReleaseHeapData_1f0f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaResReleaseHeapData_1f0f70(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetCharaDataMgr_1fdb70());
    r1 = (CharaDataReleaseHeapRecs_1ed7d0(r0), (s32)0);
    r2 = (IdBitmapClearAll_1f5270((p0 + 0xD04)), (s32)0);
    return r2;
}
