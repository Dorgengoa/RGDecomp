#include "types.h"

extern void *D_00482360;
extern void *D_0048238C;
extern void *D_0048235C;
extern u8 D_00482E10;
extern u8 D_00482E14;
extern s32 D_00482E18;
extern f32 D_0047D620;
extern f32 D_0047D628;
extern f32 D_0047D62C;
extern f32 D_0047D588;
extern f32 D_0047D5D0;
extern f32 D_0047D5B8;
extern f32 D_0047D630;
extern f32 D_0047D638;

extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void UiSetWidgetVisible_290010(void *o, s32 id, s32 a, s32 b);
extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern void UiMoveWidgetUniform_290f50(void *o, s32 id, s32 x, s32 y, s32 z, f32 t);
extern void RevelationBoardFadeInOut_34cf70(void *o, s32 a);
extern void *GetGameData_1fede0(void);
extern void RevelationBoardRefreshMaybe_3eaec0(void *o, s32 a, s32 b);
extern f32 UiGetWidgetAlpha_290770(void *o, s32 id);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);

s32 RevelationBoardClose_347b90(s32 unused, s32 en)
{
    if (en != 0) {
        D_00482E10 = 0;
        D_00482E14 = 0;
        D_00482E18 = 0;
        UiFadeWidgetAlpha_290690(D_00482360, 0x187, 1.0f, D_0047D620, -1.0f);
        UiSetWidgetVisible_290010(D_00482360, 0x187, 1, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x18D, 0, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x47, 0.0f, D_0047D628, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4A, 0.0f, D_0047D62C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x50, 0.0f, D_0047D588, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x50, -0x30, -0x30, 0, D_0047D5D0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x49, 0.0f, D_0047D588, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x49, -0x30, -0x30, 0, D_0047D5D0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4B, 0.0f, D_0047D588, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x4B, -0x96, 0x153, 0, D_0047D5B8);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5A, 0.0f, D_0047D630, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5C, 0.0f, D_0047D630, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5D, 0.0f, D_0047D630, -1.0f);
        RevelationBoardFadeInOut_34cf70(D_0048238C, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4F, 0.0f, D_0047D628, -1.0f);
        UiSetWidgetVisible_290010(D_00482360, 1, 1, -1);
        UiSetWidgetVisible_290010(D_00482360, 0xB, 1, -1);
        RevelationBoardRefreshMaybe_3eaec0(GetGameData_1fede0(), -1, 0);
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0x47) < D_0047D638) {
        StateMachineSetState_28ede0(D_0048235C, 0x70, 0);
    }
    return 1;
}
