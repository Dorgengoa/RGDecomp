/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/MenuItemScreenCloseState_2b17e0.s and build/b_drafts/MenuItemScreenCloseState_2b17e0.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern u8 *GetGameData_1fede0(void);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern void EventCondRefreshAllMaybe_1fe4f0(void);
extern void MenuItemCloseSlideStep_2b1cf0(void);
extern s32 UiWidgetIsMoving_290d30(s32, s32);
extern void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern f32 D_0047D5E4;
extern f32 D_0047D614;
extern f32 D_0047D778;
extern s32 D_0048235C;
extern s32 D_00482360;
extern u8 *D_00482374;
extern u8 D_0048241C;
extern s32 D_004824D8;
extern u8 D_004DB430[];

s32 MenuItemScreenCloseState_2b17e0(s32 arg0, s32 arg1)
{
    s32 sp2C;
    s32 sp28;
    u8 *p;

    if (arg1 != 0) {
        D_004824D8 = 0;
        UiMoveWidget_290e00(D_00482360, 0x65, 0x264, 0x49, 3, D_0047D614, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x65, 0.0f, D_0047D778, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x227, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 3, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 2, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A9, 0.0f, 2.0f, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x103, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x74, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 0, 1);
        p = GetGameData_1fede0();
        if (StateFlagTest_3ccd70(*(s32 *)(p + 0x10), 0x7F8) != 0) {
            StateFlagSet_3ccb70(*(s32 *)(p + 0x10), 0x7F8, 0, 1);
            EventCondRefreshAllMaybe_1fe4f0();
        }
    }
    MenuItemCloseSlideStep_2b1cf0();
    if (UiWidgetIsMoving_290d30(D_00482360, 0x16) == 0) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 0, 0x16, 0xD, D_00482360);
    }
    if (D_004824D8 == 3) {
        UiMoveWidget_290e00(D_00482360, 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        D_004824D8 = 4;
    } else if (D_004824D8 == 4) {
        UiGetWidgetPos_2910a0(D_00482360, 1, &sp2C, &sp28);
        if (sp2C == -0x40 && sp28 == -0x40) {
            UiSetWidgetColor_2905b0(D_00482360, 0x65, 1.0f, 1.0f, 1.0f, 0.0f);
            p = UiGetWidgetSprite_28fe10(D_00482360, 0x66, 0);
            if (p == NULL) {
                return 0;
            }
            *(f32 *)(p + 0x14) = 5.0f;
            if (*(s16 *)(D_00482374 + 0x70) != 0 || D_0048241C != 0) {
                StateMachineSetState_28ede0(D_0048235C, 3, 1);
            } else {
                StateMachineSetState_28ede0(D_0048235C, 2, 0);
            }
        }
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
