#include "types.h"

typedef struct S3460b0 {
    u8 pad00[0x7A2];
    u8 m7A2;
} S3460b0;

extern void *D_00482360;
extern void *D_0048235C;
extern S3460b0 *D_0048238C;
extern const f32 D_0047D584 __attribute__((section(".sdata")));
extern f32 D_0047D588;
extern f32 D_0047D58C;
extern f32 D_0047D590;
extern f32 D_0047D518;
extern f32 D_0047D594;
extern f32 D_0047D598;
extern f32 D_0047D59C;

extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void UiMoveWidgetUniform_290f50(void *o, s32 id, s32 x, s32 y, s32 z, f32 t);
extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern void UiSetWidgetAlpha_2907a0(void *o, s32 id, f32 t);
extern f32 UiGetWidgetAlpha_290770(void *o, s32 id);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);

s32 RevelationBoardFadeOutState_3460b0(s32 unused, s32 en)
{
    if (en != 0) {
        D_0048238C->m7A2 = 1;
        UiFadeWidgetAlpha_290690(D_00482360, 0x53, 0.0f, D_0047D584, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4B, 0.0f, D_0047D588, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x4B, -0x96, 0x153, 0, D_0047D58C);
        UiFadeWidgetAlpha_290690(D_00482360, 0x52, 0.0f, D_0047D590, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x51, 0.0f, D_0047D590, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x52, 0x15A, 0x188, 0, D_0047D518);
        UiMoveWidgetUniform_290f50(D_00482360, 0x51, 0x15D, 0x18B, 0, D_0047D518);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5A, 0.0f, D_0047D594, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5C, 0.0f, D_0047D594, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5D, 0.0f, D_0047D594, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4F, 0.0f, D_0047D594, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x47, 0.0f, D_0047D598, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x24F, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x24F, 1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0x47) < D_0047D59C) {
        StateMachineSetState_28ede0(D_0048235C, 0xB5, 0);
    }
    return 1;
}
