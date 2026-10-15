#include "types.h"

extern s32 PadIsTriggered_1839f0(void *, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern void MenuGridCursorRequestSe_28e9e0(void *, s32);
extern void *UiEntryListFindByTag_28ea40(void *, s32);
extern void UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern void *UiEntryListGetCurrentData_28ec60(void *);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s16, s16);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuInfoBoxFade_340440(s32, s32, s32, s32, s32, s32, f32);
extern void MenuWidgetPulseColor_340d40(s32, s32, s32);
extern void MenuPartyIconsMarkLearnableMaybe_340de0(s32, s32);
extern s32 MenuCharaAbilityPageSeek_3411b0(s32);
extern void MenuCycleCharaSel_341220(void *, s32);
extern void MenuCharaAbilityPageSetRowRange_341ba0(void);

extern f32 D_0047D5D0;
extern f32 D_0047D658;
extern f32 D_0047D65C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern void *D_00482364;
extern s32 D_00482378;
extern s32 D_00482D14;
extern u8 D_004B2570[0x10];

s32 MenuCharaAbilityPageSelectState_341980(s32 arg0, s32 arg1)
{
    s32 v;
    u8 *p;
    u8 *q;
    s32 x;
    s32 y;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x19, 0);
        MenuCharaAbilityPageSetRowRange_341ba0();
        MenuPartyIconsMarkLearnableMaybe_340de0(D_00482378, 0x19C);
    }
    v = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    p = (u8 *)UiEntryListGetCurrentData_28ec60(D_00482364);
    MenuWidgetPulseColor_340d40(D_00482378, 0x19C, 0);
    if (v == 2) {
        MenuInfoBoxFade_340440(D_00482378, 0, 0x1A0, 0x19F, 0x64, 0x146, D_0047D5D0);
        StateMachineSetState_28ede0(D_0048235C, 0x7D, 0);
    } else if (*(s32 *)((u8 *)D_00482364 + 0x14) == 1) {
        MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, -0x28, 0, D_0047D658);
        UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, -0x25, 0, D_0047D658);
        StateMachineSetState_28ede0(D_0048235C, 0x71, 0);
        q = (u8 *)UiEntryListFindByTag_28ea40(D_00482364, 0x18);
        x = *(s16 *)(q + 0x4);
        y = *(s16 *)(q + 0x6);
        UiSetWidgetPos_290f60(D_00482360, 0x19E, x, y);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x18D, 0, 1);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0xC) != 0) {
        MenuCycleCharaSel_341220(p, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        SoundPlayScaledVolume_1b9520(D_00482D14, 5, 0, 1.0f);
        MenuInfoBoxFade_340440(D_00482378, MenuCharaAbilityPageSeek_3411b0(*(s16 *)(p + 0x12) + *(s16 *)(p + 0x16)), 0x1A0, 0x19F, 0x64, 0x146, D_0047D5D0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 0.0f, D_0047D65C, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0xB3, 0);
    }
    return 1;
}
