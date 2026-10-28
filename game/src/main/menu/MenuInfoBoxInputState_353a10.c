/* rgp:protos */
#define RGP_SELF_MenuInfoBoxInputState_353a10 1
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
extern f32 D_0047D5E0;
extern f32 D_0047D5F0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_0048237C;
extern s32 D_00482F18;
extern u8 D_004B2570[0x10];

s32 MenuInfoBoxInputState_353a10(s32 arg0, s32 arg1)
{
    s32 v;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0xCD, 0.0f, D_0047D5F0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0xCE, 0.0f, D_0047D5F0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0xCF, 0.0f, D_0047D5F0, -1.0f);
    } else {
        v = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        if (v != 2 && v != 1 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            SoundPlayScaledVolume_1b9520(D_00482F18, 6, 0, 1.0f);
        }
        if (v == 2 || v == 1 || PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            MenuInfoPopupShowTextMaybe_355b60(D_0048237C, 0, 0x1AA, 0x1A9, 0x5D, 0x146, D_0047D5D0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 1.0f, D_0047D5E0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0xCD, 1.0f, D_0047D5D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0xCE, 1.0f, D_0047D5D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0xCF, 1.0f, D_0047D5D0, -1.0f);
            StateMachineSetState_28ede0(D_0048235C, 0xA0, 0);
        }
    }
    return 1;
}
