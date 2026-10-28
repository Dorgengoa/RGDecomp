/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuAbilityListStartState_502920 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00502920 -- f(void *, s32) state handler: the whole body is guarded
 * on `b` and every path returns 1. */

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_004844A0;          /* gp - 0xCD0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuAbilityListStartState_502920(void *a, s32 b)
{
    if (b != 0) {
        normal_BtlChgPageScrollReset_5052c0(D_00484454);
        normal_BtlChgPageSetDetailShown_506110(D_00484454, 0);
        StateMachineSetState_28ede0(D_00484498, 0x55F3, 0);
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F1, 1);
    }
    return 1;
}
