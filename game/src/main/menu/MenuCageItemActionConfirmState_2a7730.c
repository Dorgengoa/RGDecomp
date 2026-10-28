/* rgp:protos */
#define RGP_SELF_MenuCageItemActionConfirmState_2a7730 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct Ent {
    u8 pad0[0x18];
    s32 unk18;
} Ent;

typedef struct Wnd {
    u8 pad0[0x4];
    s16 unk4;
    u8 pad6[0xA];
    s16 unk10;
    u8 pad12[0x2];
    s16 unk14;
} Wnd;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_0047ECC0;
extern s16 D_0047ECC2;
extern s16 D_0047ECC4;
extern s16 D_0047ECC8;
extern s16 D_0047ECCA;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Ent *D_00482374;
extern s32 D_004823D8;
extern s8 D_00482498;
extern u8 D_004B2570[];

s32 MenuCageItemActionConfirmState_2a7730(void *self, s32 init) {
    s32 x;
    s32 y;
    s16 tbl2[2];
    s16 tbl[3];
    Wnd *w;
    s32 msg;
    Ent *e;
    s32 r;
    s32 h;
    s32 ret;
    s32 v;

    if (init != 0) {
        tbl[0] = D_0047ECC0;
        tbl[1] = D_0047ECC2;
        tbl[2] = D_0047ECC4;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x143, 1, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x25, 0);
        w = ((Wnd *)UiEntryListFindByTag_28ea40(D_00482364, 0x25));
        w->unk14 = 1;
        msg = ((s32)GetMenuResGroup_206a40());
        if (D_00482498 == 0) {
            w->unk4 = 0x78;
            UiSetWidgetSprites_290b90(D_00482360, 0x143, ResGroupListFindValueById_42c3a0(msg, 0x1E1));
            UiSetWidgetSprites_290b90(D_00482360, 0x145, ResGroupListFindValueById_42c3a0(msg, 0x1EB));
            UiSetWidgetPos_290f60(D_00482360, 0x144, 0x39, 0);
            UiSetWidgetPos_290f60(D_00482360, 0x143, 0x52, 0x9F);
        } else {
            w->unk4 = 0x3F;
            UiSetWidgetSprites_290b90(D_00482360, 0x143, ResGroupListFindValueById_42c3a0(msg, 0x1E0));
            UiSetWidgetSprites_290b90(D_00482360, 0x145, ResGroupListFindValueById_42c3a0(msg, 0x1EA));
            UiSetWidgetPos_290f60(D_00482360, 0x144, 0, 0);
            UiSetWidgetPos_290f60(D_00482360, 0x143, 0x8D, 0x9F);
        }
        v = 0xA;
        if (D_00482498 == 2) v = 0x16;
        UiSetTextY_28f550(D_00482360, 0x144, v, 0);
        UiSetTextString_28f510(D_00482360, 0x144, MsgTableLookup_28aa30(D_004823D8, tbl[D_00482498]), 0);
        UiSetTextString_28f510(D_00482360, 0x144, MsgTableLookup_28aa30(D_00481BBC, 0x52), 1);
        UiSetTextString_28f510(D_00482360, 0x144, MsgTableLookup_28aa30(D_00481BBC, 0x53), 2);
        GetGridCellPos_28ed30(&w->unk4, &x, &y);
        UiSetWidgetPos_290f60(D_00482360, 0x146, x, y);
        { s16 *pt = tbl2; pt[0] = D_0047ECC8; pt[1] = D_0047ECCA; }
        UiSetSpriteU_28f930(D_00482360, 0x144, tbl2[w->unk14], 0);
        UiSetSpriteU_28f930(D_00482360, 0x144, tbl2[(u8)((w->unk14 != 0) ^ 1)], 1);
    }
    w = ((Wnd *)UiEntryListGetCurrentData_28ec60(D_00482364));
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    if (r == 1) {
        if (w->unk10 == 0) {
            if (D_00482498 == 0) {
                e = ((Ent *)GetGameData_1fede0());
                if (e == 0) return 0;
                h = ((s32)InvFindInCategoryRange_3c8370(e->unk18, *(s32 *)((u8 *)D_00482374 + 0x6C), 0, -1, 0, 0));
                if (h != 0) {
                    h = ((s32)InvObjCastToItem4B0_3d3cd0(h, 0, 0, 0));
                    if (h != 0) CageRecRecall_3d0a20(h);
                }
                StateMachineSetState_28ede0(D_0048235C, 9, 0);
            } else if (D_00482498 == 1) {
                StateMachineSetState_28ede0(D_0048235C, 0xAE, 0);
            } else if (D_00482498 == 2) {
                e = ((Ent *)GetGameData_1fede0());
                if (e == 0) return 0;
                h = ((s32)InvFindInCategoryRange_3c8370(e->unk18, *(s32 *)((u8 *)D_00482374 + 0x6C), 0, -1, 0, 0));
                if (h != 0) {
                    h = ((s32)InvObjCastToItem4B0_3d3cd0(h, 0, 0, 0));
                    if (h != 0) CageRecClearBait_3d0c00(h);
                }
                StateMachineSetState_28ede0(D_0048235C, 9, 0);
            }
        } else {
            StateMachineSetState_28ede0(D_0048235C, 9, 0);
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0x143, 0, 1);
    } else if (r == 2) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x143, 0, 1);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
