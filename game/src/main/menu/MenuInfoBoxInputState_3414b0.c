/* rgp:protos */
#define RGP_SELF_MenuInfoBoxInputState_3414b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;
extern f32 D_0047D648;
extern f32 D_0047D64C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482378;
extern s32 D_00482D14;
extern u8 D_004B2570[0x10];

s32 MenuInfoBoxInputState_3414b0(s32 arg0, s32 arg1)
{
    s32 v;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x195, 0.0f, D_0047D64C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x196, 0.0f, D_0047D64C, -1.0f);
    } else {
        v = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        if (v != 2 && v != 1 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            SoundPlayScaledVolume_1b9520(D_00482D14, 6, 0, 1.0f);
        }
        if (v == 2 || v == 1 || PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            MenuInfoBoxFade_340440(D_00482378, 0, 0x1A0, 0x19F, 0x64, 0x146, D_0047D5D0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 1.0f, D_0047D648, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x195, 1.0f, D_0047D5D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x196, 1.0f, D_0047D5D0, -1.0f);
            StateMachineSetState_28ede0(D_0048235C, 0x7C, 0);
        }
    }
    return 1;
}
