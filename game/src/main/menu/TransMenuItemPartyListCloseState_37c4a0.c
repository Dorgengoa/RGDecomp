/* rgp:protos */
#define RGP_SELF_TransMenuItemPartyListCloseState_37c4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D968 __attribute__((section(".sdata")));
extern void *D_00484710 __attribute__((section(".sdata")));
extern void *D_0048470C __attribute__((section(".sdata")));
extern u8 D_004E9230[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemPartyListCloseState_37c4a0(void)
{
    UiFadeWidgetAlpha_290690(D_00484710, 0x7617, 0.0f, D_0047D968, -1.0f);
    UiFadeWidgetAlpha_290690(D_00484710, 0x761A, 0.0f, *(volatile const f32 *)&D_0047D968, -1.0f);
    StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
