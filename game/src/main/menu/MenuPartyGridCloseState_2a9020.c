/* rgp:protos */
#define RGP_SELF_MenuPartyGridCloseState_2a9020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern f32 D_0047D6E4;
extern f32 D_0047D6EC;
extern u8 D_004DB430[];

s32 MenuPartyGridCloseState_2a9020(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0xAC, 0.0f, D_0047D6E4, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB4, 0.0f, D_0047D6E4, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D6EC, -1.0f);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
    StateMachineSetState_28ede0(D_0048235C, 9, 0);
    return 1;
}
