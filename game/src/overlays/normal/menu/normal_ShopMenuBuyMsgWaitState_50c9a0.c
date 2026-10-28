/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyMsgWaitState_50c9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050C9A0 -- head of the 0x0050F8E0 pair.  The tested value is
 * func_28E170's result (saved in the `jal` delay slot), not func_28EC60's,
 * whose result is discarded.  ARM A of the range-test spelling: an unsigned
 * biased compare. */
extern u8    D_004B2570[];
extern void *D_004845C4;              /* gp - 0xBAC */
extern void *D_004845D0;              /* gp - 0xBA0 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyMsgWaitState_50c9a0(void)
{
    s32 v;

    v = MenuGridCursorInput_28e170(D_004845D0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004845D0);
    if ((u32)(v - 1) < 2) {
        StateMachineSetState_28ede0(D_004845C4, 0x7540, 0);
    }
    return 1;
}
