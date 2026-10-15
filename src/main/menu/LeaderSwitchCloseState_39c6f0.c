#include "types.h"


extern u8 D_004E9610[];

extern f32   D_0047D7D4;
extern u8    D_0048361C;
extern u8    D_00483638;

extern void  UiFadeWidgetAlpha_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern f32   UiGetWidgetAlpha_290770(void *p, u16 id);
extern void  UiSetWidgetsVisibleById_291110(void *p, u16 id, s32 c, s32 d);

s32 LeaderSwitchCloseState_39c6f0(void *a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_004E9610, 3, 0.0f, D_0047D7D4, -1.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 2, 0.0f, D_0047D7D4, -1.0f);
        UiFadeWidgetAlpha_290690(D_004E9610, 1, 0.0f, D_0047D7D4, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_004E9610, 3) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_004E9610, 3, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004E9610, 2, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004E9610, 1, 0, 1);
        D_0048361C = 0;
        D_00483638 = 0;
    }
    return 1;
}
