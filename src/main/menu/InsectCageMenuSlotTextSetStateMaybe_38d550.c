#include "types.h"

extern void UiSetWidgetColor_2905b0(s32, u16, f32, f32, f32, f32);
extern void UiSetTextColor_290a40(s32, u16, s32, s32);
extern f32 D_00463E40[8];
extern s32 D_00463E48[8];
extern s32 D_00483308;

void InsectCageMenuSlotTextSetStateMaybe_38d550(s32 arg0, s32 arg1) {
    f32 f;
    s32 v;
    s32 i;

    f = D_00463E40[arg1];
    UiSetWidgetColor_2905b0(D_00483308, (u16)(arg0 + 0x7580), f, f, f, 1.0f);
    v = D_00463E48[arg1];
    for (i = 0; i < 5; i++) {
        UiSetTextColor_290a40(D_00483308, (u16)(arg0 + 0x7580), v, i);
    }
}
