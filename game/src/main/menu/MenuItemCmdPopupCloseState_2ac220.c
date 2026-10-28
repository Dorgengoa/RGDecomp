/* rgp:protos */
#define RGP_SELF_MenuItemCmdPopupCloseState_2ac220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482374;
extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D708;
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuItemCmdPopupCloseState_2ac220(void)
{
    MenuShowMoneyAndItemCounts_2a32d0(D_00482374, 0x31, 0x30);
    UiFadeWidgetAlpha_290690(D_00482360, 0x89, 0.0f, D_0047D708, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482360, 0x7D, 0.0f, D_0047D708, -1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    return 1;
}
