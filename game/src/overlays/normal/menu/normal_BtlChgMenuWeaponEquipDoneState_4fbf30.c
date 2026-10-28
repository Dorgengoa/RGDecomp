/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponEquipDoneState_4fbf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FBF30 -- close arm for widget 0x49; $4 is unused, the guard is
 * on the SECOND parameter and shares the prologue's `sd $31` delay slot. */

extern void    *D_0048449C;       /* gp - 0xCD4 */
extern void    *D_00484498;       /* gp - 0xCD8 */
extern u8 normal_D_005278E0[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponEquipDoneState_4fbf30(void *unused, s32 show)
{
    if (show != 0) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x49, 0, 1);
    }
    UiSelFrameAnimStep_28d820(normal_D_005278E0, 0x28);
    StateMachineSetState_28ede0(D_00484498, 0x5602, 0);
    return 1;
}
