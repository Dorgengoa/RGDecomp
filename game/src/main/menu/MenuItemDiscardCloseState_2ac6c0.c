/* rgp:protos */
#define RGP_SELF_MenuItemDiscardCloseState_2ac6c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00482360;
extern s32 D_0048235C;
extern s8 D_0048249C;
extern f32 D_0047D710;
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuItemDiscardCloseState_2ac6c0(s32 a, s32 flag)
{
    if (flag != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0xA0, 0.0f, D_0047D710, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0xA0) <= 0.0f) {
        if (D_0048249C == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0xA, 0);
        } else {
            StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
        }
    }
    return 1;
}
