#include "types.h"
#pragma optimization_level 3

typedef struct { u8 pad[0x10]; } Buf;
typedef struct { u8 pad0[4]; u8 body[0xC]; s16 f10; s16 f12; s16 f14; s16 f16; } Wnd;
typedef struct {
    u8 pad0[0x10];
    s8 f10;
    s8 f11;
    u8 pad12[0x2C - 0x12];
    s32 f2C;
    s32 f30;
    u8 pad34[8];
    s32 f3C;
    u8 f40;
    u8 pad41[0x6C - 0x41];
    s32 f6C;
} Menu;
typedef struct { u8 pad0[0x22]; u8 f22; } Lay;
typedef struct { u8 pad0[0x74]; s16 f74; u8 pad76[0x95 - 0x76]; u8 f95; } Party;
typedef struct { u8 pad0[0x26]; s16 f26; } QC;
typedef struct { u8 pad0[0xC]; QC *fC; u8 pad10[8]; s32 f18; } Game;
typedef struct { u8 pad0[0xA]; u8 b0 : 1; u8 rest : 7; } Flg;
class Item {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual s32 Get();
};

extern "C" {
Game *GetGameData_1fede0(void);
void UiHideWidgetIfFaded_2a59e0(Menu *, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
void UiEntryListSelectByTag_28ea90(Lay *, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
Wnd *UiEntryListFindByTag_28ea40(Lay *, s32);
void GetGridCellPosOffset_28ecd0(u8 *, s32 *, s32 *, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
Item *MenuGetItemAtCell_2a7000(s32, void *);
void MenuItemInfoWidgetsCache_2a65f0(Buf *);
void MenuItemInfoPopupShow_2a33e0(Menu *, Item *, s32, s32, Buf *, s32, s32, s32, f32);
void UiSelFrameSetGridCell_28db00(void *, s32, s32, s32, s32, s32);
void MenuCageBaitIconUpdate_2a7370(Item *, s32);
s32 MenuGetMode_2a4e30(Menu *);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void MenuItemPageRefresh_2a03d0(Menu *, s32, s32, s32, s32, s32, s32);
s32 MenuGridCursorInput_28e170(Lay *, void *, s32, s32);
Wnd *UiEntryListGetCurrentData_28ec60(Lay *);
s32 MenuWeaponCombineUpdate_362920(Party *, s32);
void UiSelFrameAnimStep_28d820(void *, s32);
void MenuWidgetPulseColor_2b3200(void);
void StateMachineSetState_28ede0(s32, s32, s32);
void MenuWeaponCombineGridRefreshMaybe_3619d0(Party *, s32);
void MenuWeaponCombineGridHighlightMatchingMaybe_361640(Party *, s32);
Flg *MenuGetSelItem_2a02d0(Menu *);
void InvClearNewFlagsMaybe_3c3490(s32);
Item *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
s32 ItemIsInsectFood_3d45b0(Item *);
s32 InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
s32 InvObjCastToItem4B0_3d3cd0(s32);
s32 ItemIsCageBait_3d0cc0(s32, Item *);
void PartyMenuCursorSet_3c0710(s32, s32, s16);
s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
s32 InvFindByInvId_3c87d0(s32, s32, s32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void MenuItemSelectLastTab_2b30d0(void);
u8 InvAllItemsUnheldFlaggedMaybe_2a6f80(void);
s32 PadIsTriggered_1839f0(void *, s32);
void MenuSetSelItem_2a02e0(Menu *, Item *);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 D_00465B18[];
extern s32 D_00465B20[];
extern f32 D_0047D76C;
extern f32 D_0047D77C;
extern f32 D_0047D780;
extern f32 D_0047D784;
extern const f32 D_0047D788 __attribute__((section(".sdata")));
extern const f32 D_0047D78C __attribute__((section(".sdata")));
extern s32 D_0048235C;
extern s32 D_00482360;
extern Lay *D_00482364;
extern Menu *D_00482374;
extern Party *D_00482384;
extern u8 D_004823CC;
extern u8 D_0048241C;
extern s16 D_00482488;
extern u8 D_0048249C;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;
extern s32 D_004824BC;
extern u8 D_004B2570[];
extern u8 D_004DB430[];

static inline u8 St2(Party *p) { s32 v = p->f95; return v; }
static inline s32 IsLast(Menu *m) { return m->f10 - 1 == m->f11; }
static inline s32 NotLast(Menu *m) { return m->f10 - 1 != m->f11; }
s32 MenuItemGridState_2b1e10(s32  raw_arg0,s32  raw_first) {
s32 arg0 = raw_arg0;
s32 first = raw_first;
    s32 x;
    s32 y;
    Buf b70;
    Buf b60;
    Buf b50;
    Buf b40;
    Game *g;
    s32 pos2;
    Wnd *w;
    Item *it;
    s32 pos;
    s32 mode;
    s32 sel;
    s32 r;
    u8 rr;
    u8 k;
    Item *x2;
    s32 y2;
    s32 z2;
    Game *g2;
    s32 i;
    s32 n;
    s32 t;

    g = GetGameData_1fede0();
    UiHideWidgetIfFaded_2a59e0(D_00482374, 0x7B);
    UiHideWidgetIfFaded_2a59e0(D_00482374, 0x151);
    UiHideWidgetIfFaded_2a59e0(D_00482374, 0x36);
    UiHideWidgetIfFaded_2a59e0(D_00482374, 0x89);
    if (first != 0) {
        if (D_004823CC != 0 || D_004824BC != 0) {
            UiMoveWidgetUniform_290f50(D_00482360, 0x36, 0x50, 0xA, 0, 0.25f);
        } else {
            UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D77C, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D77C, -1.0f);
            GetGridCellPosOffset_28ecd0(UiEntryListFindByTag_28ea40(D_00482364, 3)->body, &x, &y, -14, 0x1C);
            UiSetWidgetPos_290f60(D_00482360, 0x227, x, y);
            UiMoveWidgetUniform_290f50(D_00482360, 0x36, 0x50, -0x26, 0, D_0047D780);
        }
        w = UiEntryListFindByTag_28ea40(D_00482364, 3);
        it = MenuGetItemAtCell_2a7000(D_00482374->f11, w->body);
        pos = w->f14 + w->f16 * 8;
        MenuItemInfoWidgetsCache_2a65f0(&b70);
        MenuItemInfoPopupShow_2a33e0(D_00482374, it, 0x1AA, 0x1A9, &b70, 0x68, 0x15E, pos, 2.0f);
        UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, w->f14, w->f16, 0x62, 0x49);
        MenuCageBaitIconUpdate_2a7370(it, 1);
        if (MenuGetMode_2a4e30(D_00482374) != 9) {
            UiSetWidgetColor_2905b0(D_00482360, 0x65, 1.0f, 1.0f, 1.0f, 1.0f);
            UiSetWidgetColor_2905b0(D_00482360, 0x76, 1.0f, 1.0f, 1.0f, 1.0f);
        }
        MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
        goto end;
    }
    mode = 6;
    if (D_004823CC != 0 && D_00482384->f95 == 6) {
        mode |= 1;
    }
    sel = MenuGridCursorInput_28e170(D_00482364, D_004B2570, mode, 0);
    w = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (D_004823CC != 0) {
        r = MenuWeaponCombineUpdate_362920(D_00482384, sel);
        k = D_00482384->f95;
        if (k == 6) {
            UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D784, -1.0f);
            if (D_00482384->f74 == 0) {
                UiFadeWidgetAlpha_290690(D_00482360, 0x78, 0.0f, D_0047D784, -1.0f);
                MenuItemInfoWidgetsCache_2a65f0(&b60);
                MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, &b60, 0x68, 0x15E, -1, 2.0f);
            }
            UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
            MenuWidgetPulseColor_2b3200();
        } else if (k == 7) {
            UiEntryListSelectByTag_28ea90(D_00482364, 0xD, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x26, 0);
        }
        rr = r;
        if (rr == 7) {
            UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D784, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x78, 0.0f, D_0047D784, -1.0f);
            MenuItemInfoWidgetsCache_2a65f0(&b50);
            MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, &b50, 0x68, 0x15E, -1, 2.0f);
        } else if (rr == 2 || rr == 4 || rr == 3) {
            UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
            D_00482364->f22 = 2;
            UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D788, -1.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, *(f32 *)&D_0047D788, -1.0f);
            if (D_00482384->f95 == 1 || St2(D_00482384) == 8) {
                MenuWeaponCombineGridRefreshMaybe_3619d0(D_00482384, 1);
            } else if (St2(D_00482384) == 2 || St2(D_00482384) == 4) {
                MenuWeaponCombineGridHighlightMatchingMaybe_361640(D_00482384, 1);
            }
            if (rr == 3) {
                MenuGetSelItem_2a02d0(D_00482374)->b0 = 0;
                InvClearNewFlagsMaybe_3c3490(g->f18);
                D_00482374->f2C = -1;
                D_00482374->f30 = -1;
                MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
            }
            w = UiEntryListFindByTag_28ea40(D_00482364, 3);
            it = InvFindByCategoryIndex_3c86e0(g->f18, 0, D_00482374->f11, w->f14, w->f16, 0);
            pos2 = w->f14 + w->f16 * 8;
            MenuItemInfoWidgetsCache_2a65f0(&b40);
            MenuItemInfoPopupShow_2a33e0(D_00482374, it, 0x1AA, 0x1A9, &b40, 0x68, 0x15E, pos2, 2.0f);
        }
        goto end;
    }
    if (D_00482488 != 0) {
        if (sel == 1) {
            x2 = InvFindByCategoryIndex_3c86e0(g->f18, 0, D_00482374->f11, w->f10, w->f12, 0);
            if (x2 == 0) {
                goto end;
            }
            if (ItemIsInsectFood_3d45b0(x2) == 0) {
                goto end;
            }
            y2 = InvFindInCategoryRange_3c8370(g->f18, D_00482374->f6C, 0, -1, 0, 0);
            if (y2 == 0) {
                goto end;
            }
            z2 = InvObjCastToItem4B0_3d3cd0(y2);
            if (z2 == 0) {
                goto end;
            }
            if (ItemIsCageBait_3d0cc0(z2, x2) == 0) {
                goto end;
            }
            StateMachineSetState_28ede0(D_0048235C, 0xB0, 0);
        } else if (sel == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0xB1, 0);
        }
        goto end;
    }
    it = MenuGetItemAtCell_2a7000(D_00482374->f11, w);
    if (sel == 1) {
        if (it != 0) {
            StateMachineSetState_28ede0(D_0048235C, 0x11, 0);
        }
        goto end;
    }
    if (sel == 2) {
        D_004824A0 = w->f10;
        D_004824A4 = w->f12;
        D_004824A8 = D_00482374->f11;
        g2 = GetGameData_1fede0();
        if (g2->fC->f26 == 1) {
            PartyMenuCursorSet_3c0710(g2->f18, 0, D_004824A0);
            PartyMenuCursorSet_3c0710(g2->f18, 1, D_004824A4);
            PartyMenuCursorSet_3c0710(g2->f18, 2, D_004824A8);
        }
        if (D_0048241C == 0) {
            goto a;
        }
        i = InvMakeIdFromCategory_3c88b0(g2->f18, 9, 0, 0, 0);
        n = InvMakeIdFromCategory_3c88b0(g2->f18, 9, 0, D_00465B18[0] - 1, D_00465B20[0] - 1);
        for (;; i++) {
            if (!InvFindByInvId_3c87d0(g2->f18, i, 0)) {
                goto next;
            }
            {
                Menu *menu=D_00482374;s8 count=*(volatile s8 *)&menu->f10;s8 index=*(volatile s8 *)&menu->f11;if(count-1 != index) {
                    UiSetWidgetAlpha_2907a0(D_00482360, 0x227, 0.0f);
                    MenuItemSelectLastTab_2b30d0();
                } else {
                    UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D78C, -1.0f);
                }
                if (InvAllItemsUnheldFlaggedMaybe_2a6f80() != 0) {
                    D_0048249C = 1;
                    StateMachineSetState_28ede0(D_0048235C, 0x33, 0);
                } else {
                    StateMachineSetState_28ede0(D_0048235C, 0xC, 0);
                }
                goto end;
            }
        next:
            if (i == n) {
                D_004824A0 = 0;
                D_004824A4 = 0;
                D_004824A8 = 0;
                g2 = GetGameData_1fede0();
                if (g2->fC->f26 == 1) {
                    PartyMenuCursorSet_3c0710(g2->f18, 0, D_004824A0);
                    PartyMenuCursorSet_3c0710(g2->f18, 1, D_004824A4);
                    PartyMenuCursorSet_3c0710(g2->f18, 2, D_004824A8);
                }
                StateMachineSetState_28ede0(D_0048235C, 0xA, 0);
                goto end;
            }
        }
a:
        StateMachineSetState_28ede0(D_0048235C, 0xA, 0);
        goto end;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        if (it == 0) {
            goto end;
        }
        MenuSetSelItem_2a02e0(D_00482374, it);
        D_00482374->f3C = it->Get();
        StateMachineSetState_28ede0(D_0048235C, 0xD, 0);
        goto end;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0) {
        if (it == 0) {
            goto end;
        }
        MenuSetSelItem_2a02e0(D_00482374, it);
        D_00482374->f40 = 2;
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D78C, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x36, 0);
        goto end;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7D, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x7D, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D78C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x7D, 1.0f, D_0047D76C, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x39, 0);
    }
end:
    return 1;
}
}
