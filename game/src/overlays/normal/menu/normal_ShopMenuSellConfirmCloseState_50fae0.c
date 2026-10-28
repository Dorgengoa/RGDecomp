/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellConfirmCloseState_50fae0 1
#include "port/game_protos.h"
#line 1
/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by
 * [[mwcc-float-literal-pool]]: D_0047D3C8 is the pool literal -0.1f.
 * 2 bad -> MATCH.  Carries a `.lit4`; n_olink.py:375 retargets it.  Bare
 * dv_osbuild reads 3 bad -- the un-retargeted displacement, not a defect. */
#include "types.h"
/* normal 0x0050FAE0 -- near-twin of normal_ShopMenuBuyConfirmCloseState_50cb60. */
extern void *D_004845CC;
extern void *D_004845C4;
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellConfirmCloseState_50fae0(void)
{
    UiFadeWidgetAlpha_290690(D_004845CC, 0x57, 0.0f, -0.1f, -1.0f);
    UiFadeWidgetAlpha_290690(D_004845CC, 0x63, 0.0f, -0.1f, -1.0f);
    UiFadeWidgetAlpha_290690(D_004845CC, 0x67, 0.0f, -0.1f, -1.0f);
    StateMachineSetState_28ede0(D_004845C4, 0x7543, 0);
    return 1;
}
