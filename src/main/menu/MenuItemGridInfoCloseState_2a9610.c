#include "types.h"

extern void UiSelFrameAnimStep_28d820(void *a, s32 b);
extern void UiEntryListSelectByTag_28ea90(s32 a, s32 b, s32 c);
extern void StateMachineSetState_28ede0(s32 a, s32 b, s32 c);
extern void UiFadeWidgetAlpha_290690(s32 a, s32 b, f32 c, f32 d, f32 e);
extern void MenuCursorBobUpdate_2a9c00(void);

extern f32 D_0047D6F0;
extern f32 D_0047D6F4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 D_004DB430[0x20];

s32 MenuItemGridInfoCloseState_2a9610(s32 arg0, s32 arg1)
{
    (void) arg0;
    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0xA4, 0.0f, D_0047D6F0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB4, 0.0f, D_0047D6F0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D6F4, -1.0f);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    MenuCursorBobUpdate_2a9c00();
    UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
    StateMachineSetState_28ede0(D_0048235C, 9, 0);
    return 1;
}
