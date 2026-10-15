#include "types.h"

extern void UiSelFrameAnimStep_28d820(void *, s32);
extern void UiFadeWidgetColor_2904e0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void UiFadeWidgetAlpha_290690(s32 arg0, u16 arg1, f32 arg3, f32 arg4, f32 arg5);
extern f32 UiGetWidgetAlpha_290770(s32 arg0, s32 arg1);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(s32);
extern void MenuWeaponCombineAutoHideTick_362700(s32);
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D674;
extern f32 D_0047D6D0;
extern f32 D_0047D710;
extern s32 D_00482360;
extern s32 D_00482384;
extern u8 D_004823CC;
extern u8 D_004DB430[];
extern const s16 D_004824F0 __attribute__((section(".sdata")));
#define W (*(s16 *)&D_004824F0)
#define R (*(volatile s16 *)&D_004824F0)

s32 MenuItemCmdFadeSequenceStep_2adce0(s32 arg1)
{
    f32 f;
    s16 t;
    s32 i;

    if (D_004823CC != 0) {
        s32 h = D_00482384;
        MenuWeaponCombineAutoHideTick_362700(h);
        MenuWeaponCombineAnimTickMaybe_361cd0(h);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    if (D_004824F0 == 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A7, 0.0f, D_0047D710, -1.0f);
        W = 1;
    } else {
        f = UiGetWidgetAlpha_290770(D_00482360, 0x1A7);
        if (f < D_0047D5D0 && R == 1) {
            UiFadeWidgetColor_2904e0(D_00482360, arg1, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D5D0);
            W = 2;
        }
        if (R > 1) {
            f = UiGetWidgetAlpha_290770(D_00482360, arg1);
            if (!(f < D_0047D35C)) {
                UiFadeWidgetColor_2904e0(D_00482360, arg1, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D674);
            } else if (f <= 1.0f) {
                t = R + 1;
                W = t;
                if (t > 8) {
                    W = 0;
                    return 1;
                }
                if (t == 4) {
                    UiFadeWidgetAlpha_290690(D_00482360, 0x7E, 0.0f, D_0047D6D0, -1.0f);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x7D, 0.0f, D_0047D6D0, -1.0f);
                    for (i = 0; i < 6; i++) {
                        UiFadeWidgetAlpha_290690(D_00482360, i + 0x83, 0.0f, D_0047D710, -1.0f);
                    }
                }
            }
        }
    }
    return 0;
}
