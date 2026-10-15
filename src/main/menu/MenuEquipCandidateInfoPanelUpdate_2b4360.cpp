#include "types.h"

typedef struct Box { s32 a, b, c, d; } Box;
typedef struct Msg { s32 m0; u8 pad4[0xAC]; } Msg;
typedef struct Rec { u8 pad0[8]; s64 m8; } Rec;
typedef struct Cell { u8 pad0[0x10]; f32 m10; u8 pad14[0xC]; } Cell;
class VA {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void v4C(void *);
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual s32 v70();
};

extern "C" {
void MsgFormat_28a9a0(void *, s32, Msg *, s32);
void MsgFormatParamsCtor_28aa00(Msg *);
s32 MsgTableLookup_28aa30(s32, s32);
Rec *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
void UiSetTextString_28f510(s32, s32, void *, s32);
void UiSetTextX_28f590(s32, s32, s32, s32);
Cell *UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuStatCompareColors_2a0490(s32, s32, s32, s32, s16 *);
void MenuDrawWeaponGrowth_2a0600(s32, s32, VA *, s32, s32, s32, s32);
void MenuItemInfoPopupShow_2a33e0(s32, VA *, s32, s32, Box *, s32, s32, s32, f32);
void MenuItemInfoWidgetsCache_2b3f00(Box *);
s32 ItemIsWeapon_3d46c0(VA *);
extern f32 D_0047D240;
extern f32 D_0047D45C;
extern s32 D_00482360;
extern s32 D_00482374;
extern s32 D_004823D8;
extern u8 D_004DB8C0[0x40];
extern u8 D_004DB900[0x40];

s32 MenuEquipCandidateInfoPanelUpdate_2b4360(VA *obj)
{
    s16 ids[6];
    Msg msg;
    Box b0;
    Box b1;
    Cell *cells;
    s32 i;
    s32 x;

    cells = UiGetWidgetSprite_28fe10(D_00482360, 0x181, 0);
    if (cells == 0) return 0;
    if (obj != 0) {
        if (ItemIsWeapon_3d46c0(obj) != 0) {
            MenuDrawWeaponGrowth_2a0600(D_00482374, D_00482360, obj, 0x162, 0x15D, 0x159, 0x160);
            for (i = 0; i < 6; i++) {
                ids[i] = UiGetWidgetSubItem_28f2b0(D_00482360, 0x15F, i)->m8;
            }
            MenuStatCompareColors_2a0490(D_00482374, D_00482360, 0x15E, 0x160, ids);
            obj->v4C(D_004DB8C0);
            UiSetTextString_28f510(D_00482360, 0x158, D_004DB8C0, 0);
            x = 0x56 - UiGetWidgetTextWidth_28f400(D_00482360, 0x158, 0) / 2;
            if (x == -1) x = 0;
            UiSetTextX_28f590(D_00482360, 0x158, x, 0);
            MsgFormatParamsCtor_28aa00(&msg);
            msg.m0 = obj->v70();
            MsgFormat_28a9a0(D_004DB900, MsgTableLookup_28aa30(D_004823D8, 0x7D5), &msg, 0);
            UiSetTextString_28f510(D_00482360, 0x181, D_004DB900, 1);
            for (i = 0; i < 9; i++) {
                cells[i].m10 = 2.0f;
            }
            UiSetTextCenteredX_28f300(D_00482360, 0x181, 0x118, 1);
            UiSetWidgetVisible_290010(D_00482360, 0x158, 1, -1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x182, 1, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x180, 1, 1);
        } else {
        for (i = 0; i < 9; i++) {
            cells[i].m10 = 1.0f;
        }
        UiSetTextX_28f590(D_00482360, 0x181, -1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x151, 0.0f, D_0047D45C, -1.0f);
        MenuItemInfoWidgetsCache_2b3f00(&b0);
        MenuItemInfoPopupShow_2a33e0(D_00482374, obj, 0x1AA, 0x1A9, &b0, 0x5D, 0x14A, -1, D_0047D240);
        }
    } else {
        for (i = 0; i < 9; i++) {
            cells[i].m10 = 1.0f;
        }
        UiSetTextX_28f590(D_00482360, 0x181, -1, 1);
        UiSetWidgetVisible_290010(D_00482360, 0x158, 0, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x182, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x180, 0, 1);
        MenuItemInfoWidgetsCache_2b3f00(&b1);
        MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, &b1, 0x5D, 0x14A, -1, D_0047D240);
    }
    return 1;
}
}
