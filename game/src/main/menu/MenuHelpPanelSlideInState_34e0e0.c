/* rgp:protos */
#define RGP_SELF_MenuHelpPanelSlideInState_34e0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047D638;
extern s32 D_0048235C;
extern s32 D_00482360;

s32 MenuHelpPanelSlideInState_34e0e0(s32 arg0, s32 arg1)
{
    (void) arg0;
    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21C, 0, 1);
        UiSetWidgetVisible_290010(D_00482360, 0x20F, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x20F, 0x200, 0x4B);
        UiMoveWidgetUniform_290f50(D_00482360, 0x20F, 0x5A, 0x4B, D_0047D638, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x20F, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 0, 1);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x83, 0);
    return 1;
}
