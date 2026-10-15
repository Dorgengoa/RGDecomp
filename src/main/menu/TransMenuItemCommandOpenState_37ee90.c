#include "types.h"

typedef struct {
    u8 pad0[0x18];
    s32 x18;
} Ctx;

typedef struct {
    u8 pad0[0xE];
    s16 xE;
    u8 pad10[4];
    s16 x14;
    s16 x16;
} Grp;

typedef struct {
    u8 pad0[0x10];
    s32 x10;
} Obj;

typedef struct {
    u8 pad0[0x11];
    s8 x11;
    u8 pad12[0x30];
    s16 x42;
} Mgr;

extern Ctx *GetGameData_1fede0(void);
extern Grp *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void TransMenuItemCmdColors_2a0d20(Mgr *, Obj *, s16, s32);
extern void MenuItemCmdSetRowHighlight_2a1800(Mgr *, s32, s32, s32, s16);
extern void MenuItemCmdPopupPlaceMaybe_2a4620(Mgr *, s32, s32, s32, s32, s32, s32, s32);
extern s32 MenuGetMode_2a4e30(Mgr *);
extern s32 MenuItemCountPanelSetupMaybe_2a53f0(Mgr *, Obj *, s32, s32, s32, s32, s32);
extern void MenuItemCmdFrameResize_2a5750(Mgr *, s32, s32);
extern void TransMenuItemCmdLabelsSet_2a5bd0(Mgr *, s32, s32);
extern Obj *InvFindByCategoryIndex_3c86e0(s32, s32, s8, s16, s16, s32);
extern s32 ItemRecKindIs6_3d4510(Obj *);
extern s32 ItemKindBelow4_3d4860(Obj *);
extern s32 ItemDefIsKindCId4B1_40e2e0(s32);
extern s32 ItemDefIsKindCId4B0_40e310(s32);

extern const f32 D_0047D98C __attribute__((section(".sdata")));
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern Mgr *D_00484740;

s32 TransMenuItemCommandOpenState_37ee90(s32 pad0, s32 arg1)
{
    s32 id;
    Grp *b;
    s16 kind;
    Grp *a;
    s16 mode;
    s32 x;
    Ctx *c;
    Obj *o;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0x10, 0);
        c = GetGameData_1fede0();
        a = UiEntryListFindByTag_28ea40(D_00484720, 0xC);
        a->x16 = 0;
        b = UiEntryListFindByTag_28ea40(D_00484720, 0xB);
        id = MenuGetMode_2a4e30(D_00484740);
        o = InvFindByCategoryIndex_3c86e0(c->x18, id, D_00484740->x11, b->x14, b->x16, 0);
        if (o == NULL) {
            return 0;
        }
        if (ItemKindBelow4_3d4860(o) != 0) {
            mode = 5;
            kind = 1;
        } else if (ItemRecKindIs6_3d4510(o) != 0) {
            mode = 4;
            kind = 3;
        } else {
            x = o->x10;
            mode = 6;
            kind = 0;
            if (ItemDefIsKindCId4B1_40e2e0(x) != 0) {
                kind = 5;
            } else if (ItemDefIsKindCId4B0_40e310(x) != 0) {
                kind = 4;
            }
        }
        a->xE = mode - 1;
        MenuItemCmdFrameResize_2a5750(D_00484740, 0x760A, kind);
        MenuItemCmdPopupPlaceMaybe_2a4620(D_00484740, 0x760A, 0x7609, b->x14, b->x16, mode, kind,
                     MenuItemCountPanelSetupMaybe_2a53f0(D_00484740, o, 0x760B, 0x760E, 0x760C, 0x760D, 1));
        TransMenuItemCmdLabelsSet_2a5bd0(D_00484740, kind, id);
        MenuItemCmdSetRowHighlight_2a1800(D_00484740, 0x760A, 0x7609, 0, kind);
        TransMenuItemCmdColors_2a0d20(D_00484740, o, kind, id);
        D_00484740->x42 = kind;
        UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 0.0f, D_0047D98C, -1.0f);
        UiSetWidgetPos_290f60(D_00484710, 0x762B, 0, 0);
    }
    StateMachineSetState_28ede0(D_0048470C, 0x23, 0);
    return 1;
}
