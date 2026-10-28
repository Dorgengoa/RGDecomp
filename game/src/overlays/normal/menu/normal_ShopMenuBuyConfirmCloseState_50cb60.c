/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyConfirmCloseState_50cb60 1
#include "port/game_protos.h"
#line 1
/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by
 * [[mwcc-float-literal-pool]]: D_0047D4BC is a float POOL LITERAL (-0.1f),
 * not a gp extern.  The recorded "retail hoists a gp float load and we do not"
 * park, and its "Do NOT sweep this" note, are both SUPERSEDED -- the axis that
 * mattered (extern vs literal) was held FIXED across all fifteen earlier
 * spellings.  2 bad -> MATCH.
 * Carries a `.lit4`; n_olink.py:375 retargets it.  Bare dv_osbuild reads 3 bad
 * -- the un-retargeted literal displacement, not a defect. */
#include "types.h"
/* normal 0x0050CB60 -- near-twin of normal_ShopMenuSellConfirmCloseState_50fae0 (different float
 * global and ids).  -0.1f is gp - 0x7CB4, INSIDE the gp window, so it is
 * not const; the 0.0f and -1.0f are inline literals. */
extern void *D_004845CC;
extern void *D_004845C4;
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyConfirmCloseState_50cb60(void)
{
    UiFadeWidgetAlpha_290690(D_004845CC, 0x50, 0.0f, -0.1f, -1.0f);
    UiFadeWidgetAlpha_290690(D_004845CC, 0x67, 0.0f, -0.1f, -1.0f);
    UiFadeWidgetAlpha_290690(D_004845CC, 0x63, 0.0f, -0.1f, -1.0f);
    StateMachineSetState_28ede0(D_004845C4, 0x7535, 0);
    return 1;
}
