/* rgp:protos */
#define RGP_SELF_MenuPartyOpenState_2bab40 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct { u16 v[6]; } Tbl6;

typedef struct Sub {
    u8 pad0[0x26];
    s16 x26;
} Sub;

typedef struct Game {
    u8 pad0[0xC];
    Sub *xC;
    u8 pad10[0x8];
    s32 x18;
} Game;

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
extern f32 D_0047D35C;
extern f32 D_0047D66C;
extern f32 D_0047D6D8;
extern f32 D_0047D6DC;
extern f32 D_0047D6E0;
extern s16 D_0047ECF0[4];
extern u16 D_0047ED10[6] __attribute__((section(".sdata")));
extern s16 D_0047ED20;
extern s16 D_0047ED22;
extern s16 D_0047ED24;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s32 D_00482538;
extern s16 D_0048253C;
extern s16 D_0048253E;
extern f32 D_00482540;
extern s16 D_0048254C;
extern s16 D_00482550;
extern s32 D_00482558;

s32 MenuPartyOpenState_2bab40(s32 pad0, s32 arg1) {
    Tbl6 ta __attribute__((aligned(16)));
    u16 tb[3];
    s32 h;
    s32 i;
    Game *g;
    s32 n1;
    s32 n2;
    s32 pos;
    s32 t;
    s32 k;
    u8 *obj;
    s32 c;
    s32 j;
    u16 id;
    s32 n3;
    s32 n4;
    s32 i2;
    s32 j2;

    if (arg1 != 0) {
        D_00482558 = SceneSoundGetSlot0HandleCur_207df0();
        D_0048235C = *(s32 *)(D_00482370 + 0x4CC);
        h = *(s32 *)(D_00482370 + 0x4C4);
        D_00482360 = h;
        D_00482364 = *(s32 *)(D_00482370 + 0x4C8);
        UiLayoutPanelFrame_28d580(*(s32 *)(((u8 *)UiFindWidget_290460(h, 0xB7)) + 0x20), 0, 0, 0x1B1, 0x176, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x10, 1);
        UiSetWidgetVisible_290010(D_00482360, 0xB6, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0xB6, 0x200, 0x42);
        UiMoveWidgetUniform_290f50(D_00482360, 0xB6, 0x42, 0x42, 0.375f, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB6, 1.0f, 0.0625f, 0.0f);
        MenuPartyMemberLabelSpritesMaybe_29f370(D_00482370, 0xF8);
        MenuPartyMemberFaceSprites_29f7f0(D_00482370, 0xF5);
        MenuPartyMemberGaugesRefresh_29f000(D_00482370, 0xEF);
        MenuPartyMemberStatValues_29edc0(D_00482370, 0xEC);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x118, 0, 1);
        UiSetWidgetVisible_290010(D_00482360, 0x119, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x11A, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x183, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x133, 0, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17E, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x11F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x120, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14B, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14C, 0, 1);
        for (i = 0; i < 6; i++) {
            UiSetWidgetColor_2905b0((s64)D_00482360, i + 0x22A, D_0047D6D8, D_0047D6D8, D_0047D6DC, 1.0f);
        }
        g = ((Game *)GetGameData_1fede0());
        n1 = PartyCountMembers_3c2010(g->x18, 1, 1);
        D_0048254C = 0;
        D_00482550 = 0;
        if (g->xC->x26 == 1) {
            D_0048254C = PartyMenuCursorGet_3c0760(g->x18, 3);
            D_00482550 = PartyMenuCursorGet_3c0760(g->x18, 4);
        }
        if (D_00482550 != 0) {
            n2 = PartyCountReserve_3c1c20(g->x18, 1, 1);
            if (n2 == 0) {
                D_00482550 = 0;
                if (n1 - 1 < D_0048254C) {
                    D_0048254C = 0;
                }
            } else if (n2 - 1 < D_0048254C) {
                D_0048254C = 0;
            }
        } else if (n1 - 1 < D_0048254C) {
            D_0048254C = 0;
        }
        pos = D_0048254C + D_00482550 * n1;
        MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x113, 0);
        MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x114, 1);
        MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x115, 2);
        MenuSetPartyEquipIcon_29ec60(D_00482370, pos, 0x116, 3);
        MenuShowCharaStats_29bb00(D_00482370, pos);
        MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, pos);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x117, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x117, 0.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x117, -0xC, 0x40);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x184, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x183, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x185, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x185, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x12F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 2, 0, 1);
        t = g->x18;
        k = PartyFindSlotOfId_3c3070(t, *(s16 *)(t + 0x18E));
        MenuSetCharaSel_29fa20(D_00482370, k);
        UiSetWidgetPos_290f60(D_00482360, 0x132, D_0047ECF0[k], -3);
        obj = ((u8 *)UiFindWidget_290460(D_00482360, 0xD7));
        if (obj != 0) {
            MenuPartyPanelIconSizesResetMaybe_29ddf0(D_00482370);
            c = ((s32)GetMenuResGroup_206a40());
            *(s32 *)(obj + 0x20) = ResGroupListFindValueById_42c3a0(c, D_00482550 + 0x3A2);
        }
        MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, 0, 0);
        MenuSetCursorPos_29faf0(D_00482370, D_0048254C, D_00482550);
        MenuLayoutPartyPanelMaybe_29cfb0(D_00482370, 0xD7, D_0048254C, D_00482550);
        MenuLayoutPartyFramesMaybe_29cb70(D_00482370, 0xB8, D_0048254C, D_00482550);
        UiSlideInWidgetPair_28d010(0x17, 0xE, D_00482360);
        UiFadeWidgetAlpha_290690(D_00482360, 0x41, 1.0f, D_0047D6E0, -1.0f);
        { s32 t_bt = PartyCountMembers_3c2010(g->x18, 1, 1); n3 = t_bt; }
        { s32 t_b4 = PartyCountReserve_3c1c20(g->x18, 1, 1); n4 = t_b4; }
        ta = *(Tbl6 *)D_0047ED10;
        for (pad0 = 0; pad0 < 3; pad0++) {
            id = pad0 + 0xDF;
            for (j = 0; j < 6; j++) {
                UiSetWidgetParent_2911a0(D_00482360, pad0 + ta.v[j], id);
            }
            if (pad0 < n3) {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 1, 1);
            } else {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 0, 1);
            }
        }
        tb[0] = D_0047ED20;
        tb[1] = D_0047ED22;
        tb[2] = D_0047ED24;
        for (i2 = 0; i2 < 7; i2++) {
            id = i2 + 0xE2;
            for (j2 = 0; j2 < 3; j2++) {
                UiSetWidgetParent_2911a0(D_00482360, i2 + tb[j2], id);
            }
            if (i2 < n4) {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 1, 1);
            } else {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 0, 1);
            }
        }
        UiSetWidgetParent_2911a0(D_00482360, 0x104, 0xB6);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x104, 1, 1);
        UiSetWidgetParent_2911a0(D_00482360, 0x102, 0xB6);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x102, 1, 1);
        UiSetWidgetParent_2911a0(D_00482360, 0x103, 0xB6);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x103, 1, 1);
        UiSetWidgetParent_2911a0(D_00482360, 0xD9, 0xB6);
        UiSetWidgetsVisibleById_291110(D_00482360, 0xD9, 1, 1);
        MenuPartyReserveFaceSprites_29ea50(D_00482370, 0xFB);
        MenuPartyReserveSlotLayoutMaybe_29c680(D_00482370, 0x104);
        MenuPartyReserveGaugesRefresh_29e4e0(D_00482370, 0x105);
        MenuPartySlotLayoutMaybe_29c970(D_00482370, 0xD9);
        D_00482538 = 0;
        D_00482540 = 0.0f;
        D_0048253C = D_0048254C;
        D_0048253E = D_00482550;
    }
    if (D_00482538 == 0) {
        f32 f = D_00482540 + D_0047D66C;
        D_00482540 = f;
        if (!(f < D_0047D35C)) {
            D_00482540 = D_0047D35C;
            D_00482538 = 1;
        }
    } else if (D_00482538 == 1) {
        D_00482540 -= D_0047D66C;
    }
    UiSetWidgetColor_2905b0(D_00482360, 0x41, D_00482540, D_00482540, D_00482540, 1.0f);
    if (D_00482540 <= 1.0f && D_00482538 == 1) {
        D_00482540 = 1.0f;
        UiSetWidgetColor_2905b0(D_00482360, 0x41, 1.0f, 1.0f, 1.0f, 1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x4B, 0);
    }
    return 1;
}
