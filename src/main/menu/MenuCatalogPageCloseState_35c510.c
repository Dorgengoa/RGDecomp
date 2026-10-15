#include "types.h"

void PadSetStickDpadThreshold_183950(void *, s32);
void PadClearRepeatAll_183960(void *);
void PadSetRepeat_183d50(void *, s32, s32, s32);
void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
u8 *UiFindWidget_290460(s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiGetWidgetAlpha_290770(s32, s32);
void UiMoveWidget_290e00(s32, s32, f32, f32, s32, s32, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
s32 MenuResLoadPoll_2992f0(void);
extern f32 D_0047D4B0;
extern f32 D_0047D5DC;
extern f32 D_0047D5E0;
extern f32 D_0047D5E4;
extern u8 D_0047F810;
extern u8 *D_00482388;
extern s32 D_00482FE8;
extern u8 D_004B2570[];

#define SYS (*(s32 *)(D_00482388 + 0x274))

s32 MenuCatalogPageCloseState_35c510(s32 arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u8 *p;

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(SYS, 0x1F6, 0, 1);
        PadClearRepeatAll_183960(D_004B2570);
        PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
        PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
    }
    if (*(u8 *)(D_00482388 + 0x270) != 0 && D_0047F810 == 0) {
        D_0047F810 = MenuResLoadPoll_2992f0() != 0;
    }
    UiGetWidgetPos_2910a0(SYS, 0x1A, &a, &b);
    if (a == -0x12 && b == 0xC) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 4, 0x1A, 0x11, SYS);
    }
    switch (D_00482FE8) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 4, 0x1A, 0x11, SYS);
        if (a < 0x1F) {
            D_00482FE8 = 1;
            UiFadeWidgetAlpha_290690(SYS, 0x41, 0.0f, D_0047D5DC, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(SYS, 0x41);
        UiFadeWidgetAlpha_290690(SYS, 0x3D, 1.0f, D_0047D5E0, -1.0f);
        p = UiFindWidget_290460(SYS, 0x3D);
        *(s16 *)(*(u8 **)(p + 0x20) + 8) = 0xA0;
        D_00482FE8 = 3;
        break;
    case 3:
        UiMoveWidget_290e00(SYS, 1, D_0047D5E4, 0.0f, -0x40, -0x40, 3);
        UiMoveWidgetUniform_290f50(SYS, 0x1E9, 0x200, 0x4C, 0, D_0047D4B0);
        UiFadeWidgetAlpha_290690(SYS, 0x1E9, 0.0f, -0.0625f, -1.0f);
        UiMoveWidgetUniform_290f50(SYS, 0x29, 0x118, -0x19, 0, D_0047D4B0);
        UiFadeWidgetAlpha_290690(SYS, 0x29, 0.0f, -0.0625f, -1.0f);
        D_00482FE8 = 4;
        break;
    case 4:
        UiGetWidgetPos_2910a0(SYS, 1, &c, &d);
        if (c == -0x40 && d == -0x40 && D_0047F810) {
            UiSetSpriteX_28fcd0(SYS, 0x22, 0, 0);
            StateMachineSetState_28ede0(*(s32 *)(D_00482388 + 0x27C), 2, 0);
            UiSetWidgetVisible_290010(SYS, 0x1E9, 0, -1);
            UiSetWidgetVisible_290010(SYS, 0x29, 0, -1);
        }
        break;
    }
    return 1;
}
