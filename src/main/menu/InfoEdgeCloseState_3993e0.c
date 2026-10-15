#include "types.h"

extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D5C8;

extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern void *UiGetWidgetSprite_28fe10(void *o, s32 id, s32 a);
extern void UiSetSpriteSizeUvSize_28f670(void *o, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void UiLayoutPanelFrame_28d580(void *w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void UiSetWidgetVisible_290010(void *o, s32 id, s32 a, s32 b);
extern void UiSetWidgetPos_290f60(void *o, s32 id, s32 x, s32 y);
extern void UiMoveWidgetUniform_290f50(void *o, s32 id, s32 x, s32 y, s32 z, f32 t);
extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);

s32 InfoEdgeCloseState_3993e0(void)
{
    void *w;

    UiSetWidgetsVisibleById_291110(D_00482360, 0x6A, 1, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x69, 1, 1);
    w = UiGetWidgetSprite_28fe10(D_00482360, 0x65, 0);
    UiSetSpriteSizeUvSize_28f670(D_00482360, 0x65, 0x40, 0x40, 0x40, 0x40, 0);
    if (w != 0) {
        UiLayoutPanelFrame_28d580(w, 0, 0, 0x186, 0x12C, 0);
    }
    UiSetWidgetVisible_290010(D_00482360, 0x20F, 0, -1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x65, 1, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x76, 1, 1);
    UiSetWidgetPos_290f60(D_00482360, 0x65, 0x200, 0x49);
    UiMoveWidgetUniform_290f50(D_00482360, 0x65, 0x62, 0x49, 0, D_0047D5C8);
    UiFadeWidgetAlpha_290690(D_00482360, 0x65, 1.0f, 0.0625f, 0.0f);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 0, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x8A, 0, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x7A, 0, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x68, 1, 1);
    StateMachineSetState_28ede0(D_0048235C, 9, 0);
    return 1;
}
