#include "types.h"

struct Obj66 {
    u8 pad0[0x14];
    f32 x14;
};

struct Obj3 {
    u8 pad0[0xE];
    s16 xE;
    u8 pad10[4];
    s16 x14;
    s16 x16;
};

struct Menu {
    u8 pad0[0x10];
    s8 x10;
    s8 x11;
};

extern "C" {
void UiSelFrameSetGridCell_28db00(u8 *, s32, s16, s16, s32, s32);
Obj3 *UiEntryListFindByTag_28ea40(s32, s32);
void UiSetSubItemX_28f1c0(s32, s32, s32, s32);
void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
Obj66 *UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiSetWidgetsVisibleById_291110(s32, s32, u8, s32);
void MenuItemPageRefresh_2a03d0(Menu *, s32, s32, s32, s32, s32, s32);
void MenuItemCategoryIconsFill_2a2cf0(Menu *, s32);
void MenuSetMode_2a4e40(Menu *, s32);
s32 MenuItemGetOpenModeMaybe_2a4ec0(Menu *);
void MenuCageBaitIconUpdate_2a7370(s32, s32);
extern f32 D_0047D278;
extern f32 D_0047D454;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu *D_00482374;
extern u8 D_004DB430[];
}

extern "C" void MenuItemModeApplyMaybe_2b36e0(s8 arg0, s16 arg1, s32 arg2) {
    bool f;
    Obj66 *p;
    Obj3 *q;

    f = false;
    if (arg1 == 0 || arg1 == 2) {
        f = true;
    }
    UiSetWidgetsVisibleById_291110(D_00482360, 0x66, f, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x75, f, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x74, f, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x77, f, 1);
    if (arg1 == 1) {
        MenuCageBaitIconUpdate_2a7370(0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6C, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x70, 0, 1);
        MenuItemCategoryIconsFill_2a2cf0(D_00482374, 0x6F);
    } else if (arg1 == 2) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x71, 1, 1);
        UiSetWidgetColor_2905b0(D_00482360, 0x65, D_0047D454, 1.0f, D_0047D278, 1.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x69, 0.5f, 0.5f, 0.5f, 1.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x6B, 1.0f, 1.0f, 1.0f, 1.0f);
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x66, 0);
        if (p == 0) {
            return;
        }
        p->x14 = 2.0f;
        q = UiEntryListFindByTag_28ea40(D_00482364, 3);
        q->xE = 1;
        if (q->x16 > 1) {
            q->x16 = 1;
        }
        MenuSetMode_2a4e40(D_00482374, 9);
        UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, q->x14, q->x16, 0x62, 0x49);
        UiSetSpriteX_28fcd0(D_00482360, 0x76, -1, 0x10);
        UiSetSubItemX_28f1c0(D_00482360, 0x77, -1, 0x10);
    } else {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x71, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6C, 0, 1);
        if (MenuItemGetOpenModeMaybe_2a4ec0(D_00482374) == 2) { s32 t = ((volatile Menu *)D_00482374)->x10; if (((volatile Menu *)D_00482374)->x11 == t - 1) {
            UiSetWidgetColor_2905b0(D_00482360, 0x65, 1.0f, 1.0f, 1.0f, 1.0f);
            p = UiGetWidgetSprite_28fe10(D_00482360, 0x66, 0);
            if (p == 0) {
                return;
            }
            p->x14 = 5.0f;
            q = UiEntryListFindByTag_28ea40(D_00482364, 3);
            q->xE = 4;
            MenuSetMode_2a4e40(D_00482374, 0);
            UiSetSubItemX_28f1c0(D_00482360, 0x77, 0, 0x10);
        } }
    }
    D_00482374->x11 = arg0;
    if (arg2 != 0) {
        MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0xFFFF, 0xFFFF);
    } else {
        MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
    }
}
