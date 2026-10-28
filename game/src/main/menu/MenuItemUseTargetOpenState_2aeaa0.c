/* rgp:protos */
#define RGP_SELF_MenuItemUseTargetOpenState_2aeaa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u16 v[6];
} IdTbl;

typedef struct {
    u8 pad0[4];
    s16 x;
    s16 y;
    u8 pad8[0xC];
    s16 f14;
    s16 f16;
} Elem;

typedef struct {
    u8 pad0[0x18];
    s32 f18;
} Party;

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
/*rgp*/
/*rgp*/
extern f32 D_0047D288;
extern f32 D_0047D6D0;
extern f32 D_0047D718;
extern IdTbl D_0047EC68 __attribute__((section(".sdata")));
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;
extern s16 D_004824C0;
extern s16 D_004824C2;

s32 MenuItemUseTargetOpenState_2aeaa0(s32 unused, s32 open) {
    IdTbl tbl __attribute__((aligned(16)));
    s32 mode;
    s32 n2;
    s32 i;
    s32 j;
    s32 n1;
    u16 id;
    s32 cnt;
    s32 r;
    Party *p;
    Elem *e;

    if (open != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x8D, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x8D, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x8D, 1.0f, D_0047D6D0, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x8D, 0x42, 0x66);
        r = MenuGetSelItem_2a02d0(D_00482374);
        if (r == 0) {
            return 0;
        }
        mode = ItemGetUseEffectTargetModeMaybe_3d4f00(r);
        UiSetWidgetPos_290f60(D_00482360, 0x8E, 0x11, 0x10);
        MenuItemUseTargetSelFrameLayout_2a0a60(D_00482374, 0, 0, mode);
        MenuItemUseTargetMemberLabelSpritesMaybe_2a2b70(D_00482374, 0xF8);
        MenuItemUseTargetMemberFaceSprites_2a2450(D_00482374, 0xF5);
        MenuItemUseTargetMemberGaugesRefresh_2a2800(D_00482374, 0xEF);
        MenuItemUseTargetMemberStatValues_2a25c0(D_00482374, 0xEC);
        p = ((Party *)GetGameData_1fede0());
        n1 = PartyCountMembers_3c2010(p->f18, 1, 1);
        n1 = (s32)(u32)n1;
        n2 = PartyCountReserve_3c1c20(p->f18, 1, 1);
        tbl = *(IdTbl *)&D_0047EC68;
        for (i = 0; i < 3; i++) {
            id = i + 0x8F;
            for (j = 0; j < 6; j++) {
                UiSetWidgetParent_2911a0(D_00482360, i + tbl.v[j], id);
            }
            if (i < n1) {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 1, 1);
            } else {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 0, 1);
            }
        }
        for (i = 0; i < 7; i++) {
            id = i + 0x92;
            UiSetWidgetParent_2911a0(D_00482360, i + 0xFB, id);
            UiSetWidgetParent_2911a0(D_00482360, i + 0x105, id);
            UiSetWidgetParent_2911a0(D_00482360, i + 0x10C, id);
            UiSetWidgetPos_290f60(D_00482360, id, 0, -0x89);
            if (i < n2) {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 1, 1);
            } else {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 0, 1);
            }
        }
        UiSetWidgetParent_2911a0(D_00482360, 0x104, 0x8D);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x104, 1, 1);
        UiSetWidgetParent_2911a0(D_00482360, 0x103, 0x8D);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x103, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x103, 0, -0x89);
        UiSetWidgetParent_2911a0(D_00482360, 0xD9, 0x8D);
        UiSetWidgetsVisibleById_291110(D_00482360, 0xD9, 1, 1);
        MenuItemUseTargetReserveFaceSprites_2a2230(D_00482374, 0xFB);
        MenuItemUseTargetReserveSlotLayoutMaybe_2a2010(D_00482374, 0x104);
        MenuItemUseTargetReserveGaugesRefresh_2a1ab0(D_00482374, 0x105);
        MenuItemUseTargetSlotLayoutMaybe_2a1940(D_00482374, 0xD9);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D718, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x227, 0x42, 0x66);
        e = ((Elem *)UiEntryListFindByTag_28ea40(D_00482364, 9));
        cnt = 0;
        if (mode == 0) {
            e->f14 = 0;
            e->f16 = 0;
            cnt = 1;
            UiSetWidgetPos_290f60(D_00482360, 0x227, e->x + 0x6C, e->y);
        } else {
            e->f14 = 2;
            e->f16 = 0;
            if (mode == 2) {
                cnt = 3;
            } else if (mode == 3) {
                cnt = 10;
            }
            UiSetWidgetPos_290f60(D_00482360, 0x227, e->x + 0x172, e->y);
        }
        for (i = 0; i < 10; i++) {
            id = i + 0x8F;
            if (i < cnt) {
                UiSetWidgetColor_2905b0(D_00482360, id, 1.0f, 1.0f, 1.0f, 1.0f);
            } else {
                UiSetWidgetColor_2905b0(D_00482360, id, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            }
        }
        D_004824C0 = 0;
        D_004824C2 = 0;
    }
    StateMachineSetState_28ede0(D_0048235C, 0x2A, 0);
    return 1;
}
