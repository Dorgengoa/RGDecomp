/* rgp:protos */
#define RGP_SELF_TransMenuItemCmdPopupCloseState_37c100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484740;
extern void *D_00484710;
extern void *D_0048470C;
extern f32 D_0047D968;
/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemCmdPopupCloseState_37c100(void)
{
    MenuShowMoneyAndItemCounts_2a32d0(D_00484740, 0x754A, 0x7549);
    UiFadeWidgetAlpha_290690(D_00484710, 0x762A, 0.0f, D_0047D968, -1.0f);
    UiFadeWidgetAlpha_290690(D_00484710, 0x7609, 0.0f, D_0047D968, -1.0f);
    StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
    return 1;
}
