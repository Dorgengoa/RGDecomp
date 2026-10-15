#include "types.h"

extern s32 PadIsHeld_183a20(void *, s32);
extern void PlayMenuSe_289ef0(s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void HelpBoardLoadSelected_34daa0(void);
extern volatile f32 D_0047D1FC;
extern f32 D_0047D3FC;
extern f32 D_0047D4B0;
extern f32 D_0047D5D0;
extern f32 D_0047D638;
extern f32 D_0047D640;
extern s16 D_0047F6EC;
extern s16 D_0047F6F0;
extern f32 D_0047F6F4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern f32 D_00482EBC;
extern s8 D_00482EC0;
extern u8 D_004B2570[0x40];

s32 MenuHelpBoardPageState_34e1a0(s32 arg0, s32 arg1)
{
    s32 st;
    f32 v;
    f32 f;
    f32 m;

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21C, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x21C, 0x200, 0x16);
        UiMoveWidgetUniform_290f50(D_00482360, 0x21C, 0x24, 0x16, 0, D_0047D638);
        UiFadeWidgetAlpha_290690(D_00482360, 0x21C, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x21D, 0xC4, 0x18F);
        UiFadeWidgetAlpha_290690(D_00482360, 0x21D, 1.0f, D_0047D640, -1.0f);
        D_0047F6F4 = 1.0f;
        D_00482EC0 = 0;
        D_00482EBC = 0.0f;
        PlayMenuSe_289ef0(0x2E);
    }
    if (D_00482EC0 == 0) {
        st = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        UiEntryListGetCurrentData_28ec60(D_00482364);
        if (st == 1 || (PadIsHeld_183a20(D_004B2570, 8) != 0 && D_0047F6F0 != D_0047F6EC)) {
            D_0047F6F0++;
            UiMoveWidgetUniform_290f50(D_00482360, 0x21C, 0x200, 0x16, 0, D_0047D4B0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x21C, 0.0f, -0.0625f, -1.0f);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 0, 1);
            D_00482EC0 = 1;
        } else if (PadIsHeld_183a20(D_004B2570, 4) != 0 && D_0047F6F0 != 1) {
            D_0047F6F0--;
            UiMoveWidgetUniform_290f50(D_00482360, 0x21C, 0x200, 0x16, 0, D_0047D4B0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x21C, 0.0f, -0.0625f, -1.0f);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 0, 1);
            D_00482EC0 = 1;
        } else if (st == 2) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x88, 0);
        }
    } else if (UiGetWidgetAlpha_290770(D_00482360, 0x21C) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21C, 0, 1);
        D_00482EC0 = 0;
        if (D_0047F6EC < D_0047F6F0) {
            StateMachineSetState_28ede0(D_0048235C, 0x88, 0);
        } else {
            HelpBoardLoadSelected_34daa0();
            StateMachineSetState_28ede0(D_0048235C, 0x86, 0);
        }
    }
    f = D_00482EBC + D_0047D3FC * D_0047F6F4;
    D_00482EBC = f;
    if (!(f <= D_0047D1FC) || f < 0.0f) {
        m = D_0047D1FC;
        if (!(f <= m)) {
            D_00482EBC = m;
        } else {
            D_00482EBC = 0.0f;
        }
        D_0047F6F4 *= -1.0f;
    }
    v = D_0047D5D0 + *(volatile f32 *)&D_00482EBC / D_0047D1FC;
    if (!(v <= 1.0f)) v = 1.0f;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x21D, v);
    return 1;
}
