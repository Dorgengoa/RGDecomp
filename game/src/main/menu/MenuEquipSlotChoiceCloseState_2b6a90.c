/* rgp:protos */
#define RGP_SELF_MenuEquipSlotChoiceCloseState_2b6a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D6A0;
extern f32 D_0047D6A8;
extern u8 D_004DB790[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuEquipSlotChoiceCloseState_2b6a90(s32 a, s32 b)
{
    if (b != 0) {
        UiSetWidgetAlpha_2907a0(D_00482360, 0x12F, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x151, 0.0f, D_0047D6A0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x183, 0.0f, D_0047D6A8, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x58, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
