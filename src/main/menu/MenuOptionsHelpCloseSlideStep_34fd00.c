#include "types.h"

extern void UiPlaceRowWidgetPairMaybe_28cf40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *UiFindWidget_290460(s32 arg0, s32 arg1);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void UiGetWidgetAlpha_290770(s32 arg0, s32 arg1);
extern void UiGetWidgetPos_2910a0(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3);
extern f32 D_0047D644;
extern f32 D_0047D648;
extern s32 D_00482360;
extern s32 D_00482EAC;

s32 MenuOptionsHelpCloseSlideStep_34fd00(void)
{
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    u8 *p;
    s16 *q;

    switch (D_00482EAC) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 7, 0x1D, 0x14, D_00482360);
        UiGetWidgetPos_2910a0(D_00482360, 0x1D, &sp1C, &sp18);
        if (sp1C < 0x1F) {
            D_00482EAC = 1;
            UiFadeWidgetAlpha_290690(D_00482360, 0x41, 0.0f, D_0047D644, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(D_00482360, 0x41);
        UiFadeWidgetAlpha_290690(D_00482360, 0x40, 1.0f, D_0047D648, -1.0f);
        p = UiFindWidget_290460(D_00482360, 0x40);
        (*(s16 **)(p + 0x20))[4] = 0xE0;
        D_00482EAC = 3;
        break;
    }
    UiGetWidgetPos_2910a0(D_00482360, 0x1D, &sp14, &sp10);
    if (sp14 == -0x12 && sp10 == 0xC) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 7, 0x1D, 0x14, D_00482360);
        p = UiFindWidget_290460(D_00482360, 0x25);
        if (p == NULL) {
            return 0;
        }
        q = *(s16 **)(p + 0x20);
        if (q == NULL) {
            return 0;
        }
        q[0] = 0;
        q[4] = 0x56;
        q[5] = 0x68;
        q[6] = 0x56;
        q[2] = 0x56;
    }
    return 0;
}
