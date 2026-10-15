#include "types.h"

/* UI page setup.  The FIRST parameter is never read -- retail copies $5, not
   $4, into the callee-saved register, so m2c's "arg1" is parameter TWO
   (memory/levers.d/im-eabi-stack-arguments.md).

   The tail (StateMachineSetState_28ede0 + return 1) is SHARED: the flag==0 guard branches
   straight to it, so the flag!=0 work is one nested block and there is a
   single return 1 at the end. */

struct Sel {
    s16 m0;
    s16 m2;
};

struct Root {
    u8  pad0[0x18];
    s32 m18;
};

struct Ent {
    u8  pad0[0x6];
    s16 m6;
};

struct Slot {
    u8  pad0[0x14];
    s16 m14;
    s16 m16;
};

struct Panel {
    u8 pad0[0x11];
    s8 m11;
};

extern u8 D_004DB430[];

extern f32 D_0047D5BC;
extern f32 D_0047D610;
extern f32 D_0047D61C;
extern s32 D_0047F6C4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern struct Panel *D_00482374;
extern struct Sel *D_0048238C;
extern s16 D_00482E28;

extern struct Root *GetGameData_1fede0(void);
extern void UiLayoutPanelFrame_28d580(s32, s32, s32, s32, s32, s32);
extern void UiSelFrameCalcTileCounts_28d9d0(u8 *);
extern void UiSelFrameInit_28da30(u8 *, s32, s32);
extern void UiSelFrameSetRect_28db40(u8 *, s32, s32, s32, s32, s32, s32, s32);
extern struct Slot *UiEntryListFindByTag_28ea40(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32  UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuFillItemCounts_2a3d90(struct Panel *, s32);
extern void MenuFillItemGrid_2a4b40(struct Panel *, s32);
extern void MenuDrawItemTabs_2a4ee0(struct Panel *, s32, s32);
extern s32  InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
extern struct Ent *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern s32  InvIdGetMidIndex_3d52b0(s32);
extern s32  InvIdGetMinorIndex_3d5440(s32);
extern s32  InvIdGetMajorIndex_3d55f0(s32);
extern s16 *RevelationBoardCellGetItemRec_3ead00(struct Root *, s32, s32, s32);
extern s32  RevelationBoardGetCells_3eb510(struct Root *, s32);

s32 RevelationItemSelectOpen_346f40(s32 unused, s32 flag)
{
    struct Root *root;
    s32 h;
    struct Sel *sel;
    s32 base;
    s32 id;
    struct Ent *ent;
    s32 k;
    s32 a;
    s32 b;
    s32 c;
    struct Slot *slot;

    root = GetGameData_1fede0();
    if (root == NULL) {
        return 0;
    }
    if (flag != 0) {
        D_00482E28 = 2;
        h = UiGetWidgetSprite_28fe10(D_00482360, 0x65, 0);
        if (h == 0) {
            return 0;
        }
        UiLayoutPanelFrame_28d580(h, 0, 0, 0x186, 0x12C, 0);
        UiSetWidgetVisible_290010(D_00482360, 0x65, 1, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x140, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x7E, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x8A, 0, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x65, 0x200, 0x49);
        UiMoveWidgetUniform_290f50(D_00482360, 0x65, 0x62, 0x49, 0, D_0047D61C);
        UiFadeWidgetAlpha_290690(D_00482360, 0x65, 1.0f, D_0047D610, 0.0f);
        UiSelFrameInit_28da30(D_004DB430, D_00482360, 0x78);
        UiSelFrameSetRect_28db40(D_004DB430, 0x78, 0x18, 0x18, 0x2A, 0x30, 0x62, 0x49);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB430);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x1A9, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x1A9, 0x68, 0x15E);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x1A9, 0.0f);
        MenuFillItemGrid_2a4b40(D_00482374, 0x76);
        MenuFillItemCounts_2a3d90(D_00482374, 0x77);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x227, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x227, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D5BC, -1.0f);
        sel = D_0048238C + 4;
        base = RevelationBoardGetCells_3eb510(root, D_0047F6C4);
        { s32 x_ = sel->m2 * 26; x_ = sel->m0 + (s32)(u32)x_;
        id = *RevelationBoardCellGetItemRec_3ead00(root, D_0047F6C4, base + x_ * 4, sel->m2); }
        if (id == 0x40F2 || id == 0x410B) {
            if (InvHasItemInCategory_3c7f40(root->m18, 0x40F2, 0, 0) != 0) {
                id = 0x40F2;
            } else if (InvHasItemInCategory_3c7f40(root->m18, 0x410B, 0, 0) != 0) {
                id = 0x410B;
            }
        }
        ent = InvFindInCategoryRange_3c8370(root->m18, id, 0, -1, 0, 0);
        a = 0;
        b = 0;
        c = 0;
        if (ent != NULL) {
            k = ent->m6;
            a = InvIdGetMajorIndex_3d55f0(k);
            b = InvIdGetMinorIndex_3d5440(k);
            c = InvIdGetMidIndex_3d52b0(k);
        }
        slot = UiEntryListFindByTag_28ea40(D_00482364, 0x1C);
        slot->m14 = b;
        slot->m16 = c;
        D_00482374->m11 = a;
        MenuDrawItemTabs_2a4ee0(D_00482374, 0x67, 0);
        MenuFillItemGrid_2a4b40(D_00482374, 0x76);
        MenuFillItemCounts_2a3d90(D_00482374, 0x77);
        UiSetWidgetVisible_290010(D_00482360, 0x151, 0, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x74, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7A, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6C, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x71, 0, 1);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x8D, 0);
    return 1;
}
