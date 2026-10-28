/* rgp:protos */
#define RGP_SELF_MenuTacticsAbilityListCloseState_353d90 1
#include "port/game_protos.h"
#line 1
#pragma opt_common_subs off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5DC;
extern f32 D_0047D5F4 __attribute__((section(".sdata")));
extern f32 D_0047D5F8 __attribute__((section(".sdata")));
extern s32 D_0048235C;
extern s32 D_00482360;

s32 MenuTacticsAbilityListCloseState_353d90(void) {
    UiFadeWidgetAlpha_290690(D_00482360, 0xC6, 0, D_0047D5F4, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 0, D_0047D5DC, -1.0f);
    UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, -0x28, D_0047D5F8, 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, -0x25, D_0047D5F8, 0);
    StateMachineSetState_28ede0(D_0048235C, 0x96, 0);
    return 1;
}
