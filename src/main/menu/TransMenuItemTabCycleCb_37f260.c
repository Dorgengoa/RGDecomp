#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s8 cnt;
    s8 sel;
    u8 pad12[0xA];
    s8 flag;
    u8 pad1d[7];
    s32 unk24;
} O37f260;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} W37f260;

typedef struct {
    u8 pad0[0x10];
    s16 x;
    s16 y;
} A37f260;

s32 PadIsTriggered_1839f0(u8 *, s32);
s32 PadIsRepeatTriggered_183dd0(u8 *, s32);
W37f260 *GetGameData_1fede0(void);
s8 *UiFindWidget_290460(s8 *, s32);
s32 MenuGetMode_2a4e30(O37f260 *);
s32 MenuGetSelMode_2a4e10(O37f260 *);
void MenuSetMode_2a4e40(O37f260 *, s32);
void TransMenuItemTabLayoutMaybe_37f0c0(s32);
void MenuItemCategoryTabsLayout_288ac0(s8 *, s32, s32, s32, s32, s32);
void MenuShowItemCount_2a02f0(O37f260 *, s32, s32, s32, s32);
s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
void TransMenuItemFetchWidgetRefs_37bdb0(u8 *);
void MenuItemInfoPopupShow_2a33e0(O37f260 *, s32, s32, s32, u8 *, s32, s32, s32, f32);
void PlayMenuSe_289ef0(s32);
void MenuFillItemCounts_2a3d90(O37f260 *, s32);
void MenuItemGridMarkInUse_2a4860(O37f260 *, s32);
void MenuFillItemGrid_2a4b40(O37f260 *, s32);
void strcpy(s8 *, s8 *);
extern s8 D_00463B98[16];
extern s8 D_00463BA8[16];
extern s32 D_004659E8[4];
extern s32 D_00465A18[4];
extern f32 D_0047D240;
extern s8 *D_00484710;
extern O37f260 *D_00484740;
extern u8 D_004B2570[0x100];

s32 TransMenuItemTabCycleCb_37f260(A37f260 *arg0) {
    u8 sp70[16];
    u8 *pad;
    s8 *b;
    s32 x;
    s32 cnt;
    s32 r;
    s8 *a;
    s32 y;
    s32 sel;
    W37f260 *w;
    s32 changed;
    s32 hl;
    s32 ok;

    pad = D_004B2570;
    sel = D_00484740->sel;
    cnt = D_00484740->cnt;
    changed = 0;
    if (PadIsTriggered_1839f0(pad, 4) != 0) {
        if (sel > 0) {
            sel--;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 4) == 0) {
            sel = cnt - 1;
            changed = 1;
        }
    } else if (PadIsTriggered_1839f0(pad, 8) != 0) {
        if (sel < cnt - 1) {
            sel++;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 8) == 0) {
            sel = 0;
            changed = 1;
        }
    }
    w = GetGameData_1fede0();
    ok = 0;
    if (changed != 0) {
        ok = 1;
    } else if (PadIsTriggered_1839f0(pad, 1) != 0 || PadIsTriggered_1839f0(pad, 2) != 0) {
        a = UiFindWidget_290460(D_00484710, 0x75F8);
        if (a == NULL) {
            return 0;
        }
        b = UiFindWidget_290460(D_00484710, 0x75FA);
        if (b == NULL) {
            return 0;
        }
        r = MenuGetMode_2a4e30(D_00484740);
        if (r == 0) {
            MenuSetMode_2a4e40(D_00484740, 1);
            D_00484740->cnt = D_00465A18[0];
            strcpy(a + 4, D_00463B98);
            strcpy(b + 4, D_00463B98);
        } else if (r == 1) {
            MenuSetMode_2a4e40(D_00484740, 0);
            D_00484740->cnt = D_004659E8[0];
            strcpy(a + 4, D_00463BA8);
            strcpy(b + 4, D_00463BA8);
        }
        TransMenuItemTabLayoutMaybe_37f0c0(MenuGetMode_2a4e30(D_00484740));
        sel = 0;
        ok = 1;
    }
    if (ok != 0) {
    D_00484740->sel = sel;
    MenuItemCategoryTabsLayout_288ac0(D_00484710, 0x75FA, 0x75FF, 0x75FE, sel, MenuGetMode_2a4e30(D_00484740));
    MenuItemGridMarkInUse_2a4860(D_00484740, 0x7600);
    MenuFillItemGrid_2a4b40(D_00484740, 0x7602);
    MenuFillItemCounts_2a3d90(D_00484740, 0x7603);
    if (D_00484740->flag != 0) {
        if (MenuGetSelMode_2a4e10(D_00484740) == MenuGetMode_2a4e30(D_00484740)) {
            MenuShowItemCount_2a02f0(D_00484740, 0x7602, 0x7600, 0x7603, D_00484740->unk24);
        }
    }
    y = arg0->y;
    x = arg0->x;
    r = MenuGetMode_2a4e30(D_00484740);
    r = InvFindByCategoryIndex_3c86e0(w->unk18, r, sel, x, y, 0);
    hl = -1;
    if (MenuGetSelMode_2a4e10(D_00484740) == MenuGetMode_2a4e30(D_00484740)) {
        hl = arg0->x + arg0->y * 8;
    }
    TransMenuItemFetchWidgetRefs_37bdb0(sp70);
    MenuItemInfoPopupShow_2a33e0(D_00484740, r, 0x762E, 0x762D, sp70, 0x68, 0x15E, hl, D_0047D240);
    PlayMenuSe_289ef0(0xB);
    }
    return 1;
}
