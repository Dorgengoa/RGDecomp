/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponListCloseState_4fe6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FE6D0 -- close arm for widgets 0x41 / 0x21; the record read at
 * +0x14 stays AT ITS USE as normal_FUN_004F4EB0's second argument. */

typedef struct Hdl { u8 pad00[0x14]; s16 f14; } Hdl;

extern void    *D_0048449C;       /* gp - 0xCD4 */
extern void    *D_004844A0;       /* gp - 0xCD0 */
extern void    *D_00484498;       /* gp - 0xCD8 */
extern u8 normal_D_00527020[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponListCloseState_4fe6d0(void *unused, s32 show)
{
    if (show != 0) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
        normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, ((Hdl *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55F2))->f14);
        normal_FieldHudPanelSelectRaise_4f4dc0(normal_D_00527020, -1);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x21, 0, 1);
        StateMachineSetState_28ede0(D_00484498, 0x55F6, 0);
    }
    return 1;
}
