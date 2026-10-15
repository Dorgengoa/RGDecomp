#include "types.h"

typedef struct Win Win;
#define H(o) (*(s16 *)((u8 *)w + (o)))

extern s32 MsgFormat_28a9a0(s32, s32, s32, s32);
extern s32 UiGetWidgetTextSize_28f430(s32, u16, s32 *, s32 *, s32);
extern s32 UiSetTextString_28f510(s32, u16, s32, s32);
extern s32 UiSetTextPos_28f5d0(s32, u16, s32, s32, s32);
extern s32 UiSetSpritePos_28fd10(s32, u16, s32, s32, s32);
extern Win *UiGetWidgetSprite_28fe10(s32, u16, s32);
extern s32 UiSetWidgetAlpha_2907a0(s32, u16, f32);
extern s32 UiSetTextStringPos_290b20(s32, u16, s32, s32, s32, s32);
extern s32 UiSetWidgetPos_290f60(s32, u16, s32, s32);
extern s32 UiSetWidgetsVisibleById_291110(s32, u16, s32, s32);
extern s32 SaveMenuMsgLookup_376b30(s32);
extern s32 SaveMsgBoxSetFrameMaybe_377270(s32, s32, s32, s32);
extern s32 SaveMsgBoxSetCursorMaybe_3773a0(s32, s32);
extern s32 SaveProgressWindowSetVisible_377740(s32, s32);
extern u16 D_0047FB04;
extern s32 D_004831D8;

void SaveMsgBoxShow_376bf0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp8C;
    s32 sp88;
    s32 mode;
    s32 x;
    s32 y;
    s32 ty;
    s32 cx;
    s32 lx;
    s32 rx;
    s32 d;
    Win *w;

    if (arg1 == 0) {
        return;
    }
    if (arg0 < 0) {
        UiSetWidgetsVisibleById_291110(arg1, D_0047FB04, 0, 1);
        SaveProgressWindowSetVisible_377740(arg1, 0);
        return;
    }
    mode = 0;
    switch (arg0) {
    case 0x4:
    case 0x14:
    case 0x8:
    case 0x5:
    case 0x15:
    case 0x12C:
    case 0x12D:
    case 0x258:
    case 0x262:
        mode = 1;
        break;
    case 0xC9:
    case 0xCA:
    case 0xCB:
        mode = 1;
        break;
    case 0x6:
    case 0x7:
        mode = 2;
        break;
    case 0x10:
        mode = 3;
        break;
    }
    UiSetWidgetsVisibleById_291110(arg1, D_0047FB04, 1, 1);
    UiSetWidgetAlpha_2907a0(arg1, D_0047FB04, 1.0f);
    UiSetTextString_28f510(arg1, D_0047FB04, MsgFormat_28a9a0(D_004831D8, SaveMenuMsgLookup_376b30(arg0), arg2, 1), 0);
    UiGetWidgetTextSize_28f430(arg1, D_0047FB04, &sp8C, &sp88, 0);
    SaveMsgBoxSetCursorMaybe_3773a0(arg1, -1);
    ty = -1;
    x = sp8C + 0x30;
    y = sp88 + 0x18;
    if (mode == 1) {
        y += 0x28;
        SaveMsgBoxSetCursorMaybe_3773a0(arg1, 0);
        cx = x >> 1;
        ty = y - 0x26;
        lx = cx - 0x48;
        rx = cx + 0x14;
        UiSetSpritePos_28fd10(arg1, D_0047FB04, lx, ty, 9);
        UiSetSpritePos_28fd10(arg1, D_0047FB04, rx, ty, 0xA);
        UiSetTextStringPos_290b20(arg1, D_0047FB04, SaveMenuMsgLookup_376b30(0x64), lx + 0xC, ty + 5, 1);
        UiSetTextStringPos_290b20(arg1, D_0047FB04, SaveMenuMsgLookup_376b30(0x65), rx + 0x12, ty + 5, 2);
        ty -= 0xC;
    }
    if (mode == 2) {
        y += 0x24;
        ty = y - 0x30;
    }
    if (mode == 3) {
        y += 0x24;
        ty = y - 0x2E;
    }
    UiSetWidgetPos_290f60(arg1, D_0047FB04, 0x100 - (x >> 1), 0xE0 - (y >> 1));
    UiSetTextPos_28f5d0(arg1, D_0047FB04, 0x18, 0xC, 0);
    SaveMsgBoxSetFrameMaybe_377270(arg1, 0x10, ty, x - 0x24);
    if (mode != 2 && mode != 3) {
        SaveProgressWindowSetVisible_377740(arg1, 0);
    }
    w = UiGetWidgetSprite_28fe10(arg1, D_0047FB04, 0);
    if (w != 0) {
        H(0x4) = x - 8;
        H(0x6) = y - 8;
        d = x - (H(0x2C) + H(0x6C));
        H(0x44) = d;
        H(0x60) = H(0x40) + d;
        H(0xE4) = d;
        H(0x100) = H(0xE0) + d;
        H(0xA0) = H(0xE0) + d;
        d = y - (H(0x2E) + H(0xCE));
        H(0x86) = d;
        H(0xC2) = H(0x82) + d;
        H(0xA6) = d;
        H(0x102) = H(0xA2) + d;
        H(0xE2) = H(0xA2) + d;
    }
}
