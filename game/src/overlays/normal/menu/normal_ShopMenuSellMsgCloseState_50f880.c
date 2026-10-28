/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellMsgCloseState_50f880 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050F880 -- the TAIL of the 0x70-widget phase-handler family
 * (normal_FUN_0050F960 / normal_FUN_0050CA10) with a single call in the guard.
 *
 * f(void *, s32): `$4` is never read, the guard is on `b`, and every path
 * returns 1.  The guarded call is one func_290690; note that against the seed
 * the float arguments are SWAPPED -- `mtc1 $0,$f12` is 0.0f in slot three and
 * `lui 0x3F80 -> BF80 / mtc1 $2,$f14` is -1.0f in slot five, with the gp
 * literal D_0047D3C8 (gp - 0x7DA8) in the middle.
 */

extern u8 normal_D_00527E70;

extern f32   D_0047D3C8;          /* gp - 0x7DA8 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellMsgCloseState_50f880(void *a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_004845CC, 0x70, 0.0f, D_0047D3C8, -1.0f);
    }
    UiSelFrameAnimStep_28d820(&normal_D_00527E70, 0x3F);
    StateMachineSetState_28ede0(D_004845C4, 0x7547, 0);
    return 1;
}
