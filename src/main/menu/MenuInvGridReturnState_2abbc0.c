#include "types.h"

extern void UiSelFrameAnimStep_28d820(void *arg0, s32 arg1);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetColor_2904e0(s32 arg0, s32 arg1, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 a, f32 b, f32 c);
extern void UiSetSpriteFlags_290bd0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 MenuGetMode_2a4e30(s32 arg0);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(s32 arg0);
extern void MenuWeaponCombineAutoHideTick_362700(s32 arg0);
extern s32 D_004659F0[4];
extern s32 D_004659F8[4];
extern f32 D_0047D278;
extern f32 D_0047D454;
extern f32 D_0047D754;
extern f32 D_0047D758;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482374;
extern s32 D_00482384;
extern u8 D_004823CC;
extern u8 D_004DB430[];

s32 MenuInvGridReturnState_2abbc0(s32 arg0, s32 arg1)
{
    s32 i;
    s32 n;
    s32 h;

    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x163, 0.0f, D_0047D754, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x151, 0.0f, D_0047D754, -1.0f);
        if (D_004823CC == 0) {
            if (MenuGetMode_2a4e30(D_00482374) == 9) {
                UiFadeWidgetColor_2904e0(D_00482360, 0x65, D_0047D454, 1.0f, D_0047D278, 1.0f, D_0047D758);
            } else {
                UiFadeWidgetColor_2904e0(D_00482360, 0x65, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D758);
            }
            i = 0;
            n = D_004659F0[0] * D_004659F8[0];
            for (; i < n; i++) {
                UiSetSpriteFlags_290bd0(D_00482360, 0x76, 0x20, -1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x74, 0x20, -1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x76, 8, 1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x76, 0x20, 1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x74, 0x20, 1, i, 0);
            }
        }
    }
    if (D_004823CC != 0) {
        h = D_00482384;
        MenuWeaponCombineAutoHideTick_362700(h);
        MenuWeaponCombineAnimTickMaybe_361cd0(h);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x12, 0);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
