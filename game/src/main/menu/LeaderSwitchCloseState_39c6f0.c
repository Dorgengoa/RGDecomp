/* rgp:protos */
#define RGP_SELF_LeaderSwitchCloseState_39c6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


extern u8 D_004E9610[];

extern f32   D_0047D7D4;
extern u8    D_0048361C;
extern u8    D_00483638;

/*rgp*/
/*rgp*/
/*rgp*/

s32 LeaderSwitchCloseState_39c6f0(void *a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_004E9610, 3, 0.0f, D_0047D7D4, -1.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 2, 0.0f, D_0047D7D4, -1.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 1, 0.0f, D_0047D7D4, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_004E9610, 3) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_004E9610, 3, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004E9610, 2, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004E9610, 1, 0, 1);
        D_0048361C = 0;
        D_00483638 = 0;
    }
    return 1;
}
