/* rgp:protos */
#define RGP_SELF_MenuRevelationNoticeCloseState_347300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D664;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuRevelationNoticeCloseState_347300(s32 a, s32 b)
{
    f32 r;

    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x64, 0.0f, D_0047D664, -1.0f);
    }
    r = UiGetWidgetAlpha_290770(D_00482360, 0x64);
    if (r <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x64, 0, 1);
        StateMachineSetState_28ede0(D_0048235C, 0x8A, 0);
    }
    return 1;
}
