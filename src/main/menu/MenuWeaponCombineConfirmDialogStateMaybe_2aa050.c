#include "types.h"

extern void *memset(void *, s32, u32);
extern f32 Sinf_128fd0(f32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void PhaseAdvanceWrapPi_28b630(f32 *, f32);
extern void UiWindowFitToText_28d0c0(void *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiSetTextX_28f590(s32, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(s32, s32, s32);
extern void UiSetSpriteU_28f930(s32, s32, s32, s32);
extern void UiSetSpriteW_28fbf0(s32, s32, s32, s32);
extern void UiSetSpriteY_28fc90(s32, s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuSetToggle_2b3a20(s32, s32);
extern void MenuWeaponCombineUpdate_362920(u8 *, s32);

extern f32 D_0047D3B8;
extern f32 D_0047D470;
extern f32 D_0047D6D0;
extern f32 D_0047D720;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 *D_00482384;
extern s32 D_004823E4;
extern f32 D_004824C8;
extern s8 D_004824CC;
extern u8 D_00483060;
extern u8 D_00483068;
extern u8 D_0048306C;
extern u8 D_00483074;
extern u8 D_004B2570[];

s32 MenuWeaponCombineConfirmDialogStateMaybe_2aa050(s32 pad0, s32 arg1) {
    s32 b[0xD];
    s32 r;
    s32 x0;
    s32 k;
    s32 x;
    s32 y;
    s16 *p;
    u8 *o;
    f32 f;

    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    if (D_00482384[0x81] != 0 && D_00483060 != 0 && D_00483068 == 0 && D_0048306C == 0 && D_00483074 == 0) {
        UiSetWidgetAlpha_2907a0(D_00482360, 0x1E7, 1.0f);
        if (arg1 != 0) {
            UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        }
        if (r == 1) {
            o = D_00482384;
            o[0x61] = 7;
            *(s32 *)(o + 0x78) = 0;
            SoundStopEntry_1b8bc0(D_004823E4, 8, 0);
            D_00482384[0x81] = 0;
            D_00482384[0x82] = 0;
            UiFadeWidgetAlpha_290690(D_00482360, 0x1E7, 0.0f, -0.0625f, -1.0f);
            StateMachineSetState_28ede0(D_0048235C, 0x22, 0);
        }
    } else if (D_00483074 != 0) {
        if (arg1 != 0) {
            UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        } else if (!(UiGetWidgetAlpha_290770(D_00482360, 0x1E7) <= D_0047D470)) {
            UiSetWidgetAlpha_2907a0(D_00482360, 0x1E7, 1.0f);
            if (r == 1 || r == 2) {
                o = D_00482384;
                o[0x61] = 7;
                *(s32 *)(o + 0x78) = 0;
                SoundStopEntry_1b8bc0(D_004823E4, 8, 0);
                StateMachineSetState_28ede0(D_0048235C, 0x22, 0);
                UiFadeWidgetAlpha_290690(D_00482360, 0x1E7, 0.0f, -0.0625f, -1.0f);
            }
        }
    } else {
        if (D_00483068 != 0 || D_0048306C != 0) {
            x0 = 0x28;
        } else {
            x0 = 0x5C;
        }
        if (arg1 != 0) {
            memset(b, 0, 0x34);
            b[0] = UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0);
            b[1] = UiGetWidgetText_28f620(D_00482360, 0x21E, 0);
            b[5] = 0x31;
            b[6] = 0x26;
            b[7] = 8;
            if (D_00483068 != 0 || D_0048306C != 0) {
                b[4] = 0xF8;
                y = -7;
            } else {
                b[4] = 0x152;
                y = 0x49;
            }
            b[9] = y;
            b[8] = 0x62;
            b[10] = 0x186;
            b[11] = 0x12C;
            *(s16 *)&b[12] = 0xC;
            UiWindowFitToText_28d0c0(b, 0, 0, 0);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x223, 1, 1);
            UiFadeWidgetAlpha_290690(D_00482360, 0x21E, 1.0f, D_0047D6D0, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x223, 1.0f, D_0047D6D0, -1.0f);
            if (D_00483068 != 0 || D_0048306C != 0) {
                p = (s16 *)b[1];
                UiSetWidgetPos_290f60(D_00482360, 0x223, p[0] - 0x26, p[1] - 0x36);
                UiSetSpriteW_28fbf0(D_00482360, 0x224, 0xCC, 1);
                UiSetSpriteX_28fcd0(D_00482360, 0x224, 0xE0, 2);
                UiSetSpriteY_28fc90(D_00482360, 0x225, 0x34, 2);
                k = 0x3E;
            } else {
                p = (s16 *)b[1];
                UiSetWidgetPos_290f60(D_00482360, 0x223, p[0] - 0x26, p[1] - 8);
                UiSetSpriteW_28fbf0(D_00482360, 0x224, 0x126, 1);
                UiSetSpriteX_28fcd0(D_00482360, 0x224, 0x13A, 2);
                UiSetSpriteY_28fc90(D_00482360, 0x225, 6, 2);
                k = 0x66;
            }
            UiSetSpriteX_28fcd0(D_00482360, 0x225, k, 0);
            UiSetSpriteX_28fcd0(D_00482360, 0x225, k + 0x50, 1);
            UiSetTextX_28f590(D_00482360, 0x225, k + 0x1A, 0);
            UiSetTextX_28f590(D_00482360, 0x225, k + 0x6A, 1);
            UiSetTextString_28f510(D_00482360, 0x225, MsgTableLookup_28aa30(D_00481BBC, 0x52), 0);
            UiSetTextString_28f510(D_00482360, 0x225, MsgTableLookup_28aa30(D_00481BBC, 0x53), 1);
            UiSetWidgetPos_290f60(D_00482360, 0x226, x0 + 0x50, 0x51);
            UiSetSpriteU_28f930(D_00482360, 0x225, 0x4C, 1);
            UiSetSpriteU_28f930(D_00482360, 0x225, 0x18, 0);
            UiSetTextCenteredX_28f300(D_00482360, 0x21E, 0x125, 0);
            UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
            D_004824CC = 1;
        } else {
            UiSetWidgetAlpha_2907a0(D_00482360, 0x1E7, 1.0f);
            if (!(UiGetWidgetAlpha_290770(D_00482360, 0x21E) <= D_0047D470)) {
                if (r == 1) {
                    if (D_004824CC == 0) {
                        if (D_00483068 != 0) {
                            D_00483068 = 0;
                        } else if (D_0048306C != 0) {
                            D_0048306C = 0;
                        } else if (D_00483074 != 0) {
                            D_00483074 = 0;
                        } else {
                            D_00483060 = 0;
                        }
                        o = D_00482384;
                        o[0x61] = 2;
                        *(s32 *)(o + 0x78) = 3;
                        StateMachineSetState_28ede0(D_0048235C, 0x23, 0);
                    } else if (D_004824CC == 1) {
                        o = D_00482384;
                        o[0x61] = 7;
                        *(s32 *)(o + 0x78) = 0;
                        SoundStopEntry_1b8bc0(D_004823E4, 8, 0);
                        StateMachineSetState_28ede0(D_0048235C, 0x22, 0);
                    }
                    UiFadeWidgetAlpha_290690(D_00482360, 0x21E, 0.0f, D_0047D720, -1.0f);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x223, 0.0f, D_0047D720, -1.0f);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x1E7, 0.0f, -0.0625f, -1.0f);
                }
                if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
                    MenuSetToggle_2b3a20(0x225, 1);
                } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
                    MenuSetToggle_2b3a20(0x225, 0);
                }
            }
            PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
            f = 8.0f * Sinf_128fd0(D_004824C8);
            UiMoveWidgetUniform_290f50(D_00482360, 0x226, f + (f32)(x0 + D_004824CC * 0x50), 0x51, 0, 0.25f);
        }
    }
    MenuWeaponCombineUpdate_362920(D_00482384, r);
    return 1;
}
