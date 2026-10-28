/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellMsgWaitState_50f8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050F8E0 -- tail of the 0x0050C9A0 pair (different event id and an
 * extra func_28D820).  The range test is the biased unsigned compare, the same
 * spelling 0x0050C9A0 closed on; a compiled `switch` costs FOUR extra words. */
extern u8    D_004B2570[];
extern u8 normal_D_00527E70[];
extern void *D_004845C4;              /* gp - 0xBAC */
extern void *D_004845D0;              /* gp - 0xBA0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellMsgWaitState_50f8e0(void)
{
    s32 v;

    v = MenuGridCursorInput_28e170(D_004845D0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004845D0);
    if ((u32)(v - 1) < 2) {
        StateMachineSetState_28ede0(D_004845C4, 0x754D, 0);
    }
    UiSelFrameAnimStep_28d820(normal_D_00527E70, 0x3F);
    return 1;
}
