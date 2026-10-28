/* rgp:protos */
#define RGP_SELF_EvTargetPointObjInitWithKey_2f9470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EvTargetPointObjInitWithKey_2f9470.  Retail tests 9 then 7 with `beql` INTO each arm:
   that is a compiled two-case switch with the case order REVERSED, so
   the source order is 7 then 9.  The common `swc1 $f20,0xE0` tail is
   duplicated into the default path's branch delay slot. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EvTargetPointObjInitWithKey_2f9470(u8 *p, s32 a, s32 b, s32 c, s32 d, s32 e, f32 fa, f32 fb)
{
    EvTargetPointObjReset_2f9550(p);
    EvObjInitWithKey_2f9e60(p, a, b);
    switch (c) {
    case 7:
        TargetRefSetMapObj_2e6470(p + 0xA0, d, e, fa);
        break;
    case 9:
        TargetRefSetMapNode_2e6370(p + 0xA0, d, e, fa);
        break;
    }
    *(f32 *)(p + 0xE0) = fb;
}
