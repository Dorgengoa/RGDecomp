#include "types.h"

extern void UiFadeWidgetColor_2904e0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg3, f32 arg4, f32 arg5);
extern f32 UiGetWidgetAlpha_290770(s32 arg0, s32 arg1);
extern void MenuWidgetFadeInOut_29fb00(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D670;
extern f32 D_0047D674;
extern s32 D_00482360;
extern s32 D_00482370;
extern const s16 D_00482568 __attribute__((section(".sdata")));
#define W (*(s16 *)&D_00482568)
#define R (*(volatile s16 *)&D_00482568)

s32 MenuPartyFadeSequenceStep_2b9240(s32 arg0, s32 arg1, s32 arg2)
{
    f32 f;
    s16 t;

    if (D_00482568 == 0) {
        UiFadeWidgetAlpha_290690(D_00482360, arg0, 0.0f, D_0047D670, -1.0f);
        W = 1;
    } else {
        f = UiGetWidgetAlpha_290770(D_00482360, arg0);
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
                    MenuWidgetFadeInOut_29fb00(D_00482370, arg2, 0, 0);
                }
            }
        }
    }
    return 0;
}
