#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

extern void ModelSetScale_150ff0(s32, V4 *);
extern void PadClearRepeatAll_183960(void *);
extern void PadSetRepeat_183d50(void *, s32, s32, s32);
extern void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern f32 D_0047D4B0;
extern f32 D_0047D5E4;
extern f32 D_0047D610;
extern f32 D_0047D618;
extern f32 D_0047D620;
extern f32 D_0047F7E0;
extern f32 D_0047F7E4;
extern s32 D_00482380;
extern u8 D_004823CC;
extern s32 D_004823D0;
extern s32 D_00482F74;
extern s32 D_00482F78;
extern u8 D_00482F98;
extern u8 D_00482F9C;
extern u8 D_004B2570[];

s32 MenuModelPageCloseState_358420(s32 arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    f32 x;
    f32 y;

    if (arg1 != 0) {
        s32 o;
        D_00482F74 = 0;
        D_0047F7E0 = 1.0f;
        D_00482F78 = -1;
        D_0047F7E4 = 1.0f;
        o = *(s32 *)(*(volatile s32 *)&D_00482380 + 0x134);
        UiSetWidgetsVisibleById_291110(o, 0x1DE, 0, 1);
        D_00482F98 = 0;
        D_00482F9C = 0;
        PadClearRepeatAll_183960(D_004B2570);
        PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
    }
    UiGetWidgetPos_2910a0(*(s32 *)(D_00482380 + 0x134), 0x1B, &a, &b);
    if (a == -0x12 && b == 0xC) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 5, 0x1B, 0x12, *(s32 *)(D_00482380 + 0x134));
    }
    switch (D_00482F74) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 5, 0x1B, 0x12, *(s32 *)(D_00482380 + 0x134));
        if (a < 0x1F) {
            D_00482F74 = 1;
            D_00482F78 = 0;
            UiFadeWidgetAlpha_290690(*(s32 *)(D_00482380 + 0x134), 0x41, 0.0f, D_0047D618, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(*(s32 *)(D_00482380 + 0x134), 0x41);
        UiFadeWidgetAlpha_290690(*(s32 *)(D_00482380 + 0x134), 0x3E, 1.0f, D_0047D610, -1.0f);
        {
            s32 p = UiFindWidget_290460(*(s32 *)(D_00482380 + 0x134), 0x3E);
            *(s16 *)(*(s32 *)(p + 0x20) + 8) = 0xA0;
        }
        D_00482F74 = 3;
        break;
    case 3:
        UiMoveWidget_290e00(*(s32 *)(D_00482380 + 0x134), 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        UiGetWidgetPos_2910a0(*(s32 *)(D_00482380 + 0x134), 0x23A, &e, &f);
        UiMoveWidgetUniform_290f50(*(s32 *)(D_00482380 + 0x134), 0x23A, 0x200, f, 0, D_0047D4B0);
        UiFadeWidgetAlpha_290690(*(s32 *)(D_00482380 + 0x134), 0x23A, 0.0f, -0.0625f, -1.0f);
        D_00482F74 = 4;
        break;
    case 4:
        UiGetWidgetPos_2910a0(*(s32 *)(D_00482380 + 0x134), 1, &c, &d);
        if (c == -0x40 && d == -0x40) {
            D_00482F98 = 1;
            UiSetWidgetVisible_290010(*(s32 *)(D_00482380 + 0x134), 0x1D1, 0, -1);
        }
        break;
    }
    switch (D_00482F78) {
    case 0:
        UiFadeWidgetAlpha_290690(*(s32 *)(D_00482380 + 0x134), 0x246, 0.0f, -0.25f, -1.0f);
        D_00482F78 = 1;
        break;
    case 1:
        if (UiGetWidgetAlpha_290770(*(s32 *)(D_00482380 + 0x134), 0x246) <= D_0047D620) {
            x = D_0047F7E0;
            x -= D_0047D610;
            D_0047F7E4 -= D_0047D610;
            D_0047F7E0 = x;
            if (x < 0.0f) {
                D_0047F7E0 = 0.0f;
            }
            if (D_0047F7E4 < 0.0f) {
                D_0047F7E4 = 0.0f;
            }
            y = D_0047F7E0;
            {
                s32 g = D_004823D0;
                V4 v = {0};
                v.x = y;
                v.y = y;
                v.z = y;
                ModelSetScale_150ff0(g, &v);
            }
            *(f32 *)(D_004823D0 + 0x170) = D_0047F7E4;
            if (D_0047F7E0 <= 0.0f && D_0047F7E4 <= 0.0f) {
                D_00482F78 = 2;
            }
        }
        break;
    case 2:
        UiSetWidgetVisible_290010(*(s32 *)(D_00482380 + 0x134), 0x246, 0, -1);
        D_004823CC = 0;
        D_00482F9C = 1;
        break;
    }
    if (D_00482F98 != 0 && D_00482F9C != 0) {
        StateMachineSetState_28ede0(*(s32 *)(D_00482380 + 0x13C), 2, 0);
    }
    return 1;
}
