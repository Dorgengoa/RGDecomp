#include "types.h"

void *UiFindWidget_290460(s32, s32);                        /* extern */
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);                 /* extern */
s32 UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);               /* extern */
s32 UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);                /* extern */
extern f32 D_0047D5D0;
extern f32 D_0047D610;
extern f32 D_0047D618;
extern s32 D_00482360;
extern s32 D_00482F24;

s32 MenuTacticsCloseSlideStep_3551f0(void) {
    s32 sp1C;
    s32 sp18;

    switch (D_00482F24) {                           /* irregular */
    case 0:
        UiMoveWidgetUniform_290f50(D_00482360, 0x18, -0x12, 0xC, 0, D_0047D5D0);
        UiMoveWidgetUniform_290f50(D_00482360, 0xF, -0xF, 0xF, 0, D_0047D5D0);
        UiGetWidgetPos_2910a0(D_00482360, 0x18, &sp1C, &sp18);
        if (sp1C < 0x1F) {
            D_00482F24 = 1;
            UiFadeWidgetAlpha_290690(D_00482360, 0x41, 0.0f, D_0047D618, -1.0f);
        }
        break;
    case 1: {
        u8 *p;
        u8 *q;

        UiFadeWidgetAlpha_290690(D_00482360, 0x3B, 1.0f, D_0047D610, -1.0f);
        p = (u8 *)UiFindWidget_290460(D_00482360, 0x3B);
        q = *(u8 **)(p + 0x20);
        *(u16 *)(q + 0x8) = 0x60;
        D_00482F24 = 3;
        break;
    }
    }
    return 0;
}
