#include "types.h"

extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern s16 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s8 *MenuGetCursorPos_29fae0(u8 *);
extern f32 D_0047D288;
extern u16 D_0047EC00[4];
extern u16 D_0047EC10[4];

s32 MenuPartyCmdListHighlight_29c440(u8 *arg0, s32 arg1, s16 arg2, s16 arg3)
{
    s32 x;
    s8 *p;
    s32 i;
    s16 *q;

    if ((u16)arg1 == 0x11A) {
        x = 0x7C;
    } else {
        x = 0x54;
    }
    p = MenuGetCursorPos_29fae0(arg0);
    for (i = 0; i < 4; i++) {
        if (p[1] == 1) {
            if (i == 3) {
                break;
            }
            UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x4C4), D_0047EC10[i], 1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x4C4), D_0047EC00[i], 1.0f, 1.0f, 1.0f, 1.0f);
        }
        if (i == arg2) {
            UiSetSpriteSizeUvSize_28f670(*(s32 *)(arg0 + 0x4C4), arg1, 0, 0, 0, 0, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(*(s32 *)(arg0 + 0x4C4), arg1, x + 0xE, 0x1C, 4, 4, i);
        }
    }
    q = UiGetWidgetSprite_28fe10(*(s32 *)(arg0 + 0x4C4), 0x118, 0);
    if (q == 0) {
        return 0;
    }
    q[0] = 5;
    q[1] = arg2 * 28 + 9;
    q[2] = x + 0xE;
    UiSetWidgetsVisibleById_291110(*(s32 *)(arg0 + 0x4C4), 0x118, 1, 1);
    if (arg3 < 0) {
        if (p[1] == 0) {
            i = D_0047EC00[arg2];
            UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x4C4), i, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        } else {
            i = D_0047EC10[arg2];
            UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x4C4), i, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        }
    }
    return 1;
}
