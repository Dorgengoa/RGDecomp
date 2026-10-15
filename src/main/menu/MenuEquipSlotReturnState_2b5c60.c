#include "types.h"

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern f32 D_0047D688;
extern f32 D_0047D690;
extern f32 D_0047D694;
extern f32 D_0047D698;
extern f32 D_0047D69C;
extern u8 D_004DB790[];

extern void MenuPartyPanelsSetVisible_2b41c0(s32 a);
extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void UiMoveWidgetUniform_290f50(void *o, s32 id, s32 x, s32 y, s32 z, f32 t);
extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern void UiGetWidgetPos_2910a0(void *o, s32 id, s32 *a, s32 *b);
extern void UiSetWidgetPos_290f60(void *o, s32 id, s32 x, s32 y);
extern void UiEntryListSelectByTag_28ea90(void *o, s32 a, s32 b);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);
extern void UiSelFrameAnimStep_28d820(void *w, s32 id);

s32 MenuEquipSlotReturnState_2b5c60(s32 unused, s32 en)
{
    s32 a;
    s32 b;

    if (en != 0) {
        MenuPartyPanelsSetVisible_2b41c0(1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x133, 0.0f, D_0047D690, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x133, 0x200, 0x42, 0, D_0047D694);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14F, 0.0f, D_0047D688, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17E, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x180, 0, 1);
        UiGetWidgetPos_2910a0(D_00482360, 0x12F, &a, &b);
        UiSetWidgetPos_290f60(D_00482360, 0x185, a + 0x38, b + 0x1E);
        UiFadeWidgetAlpha_290690(D_00482360, 0x185, 1.0f, D_0047D698, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x14C, -0x28, 0, D_0047D69C);
        UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x14F, -0x25, 0, D_0047D69C);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x14, 1);
        StateMachineSetState_28ede0(D_0048235C, 0x5B, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
