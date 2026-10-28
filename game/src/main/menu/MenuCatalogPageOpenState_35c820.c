/* rgp:protos */
#define RGP_SELF_MenuCatalogPageOpenState_35c820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx {
    u8 pad0[0x8];
    s32 m8;
} Ctx;

typedef struct Ent {
    u8 pad0[0x20];
    s32 m20;
} Ent;

typedef struct Spr {
    u8 pad0[0x16];
    s16 m16;
    u8 pad18[2];
    s16 m1A;
} Spr;

typedef struct Mgr {
    u8 pad0[0x274];
    s32 m274;
    s32 m278;
    s32 m27C;
} Mgr;

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
extern f32 D_0047D5C8;
extern f32 D_0047D5E0;
extern f32 D_0047D5EC;
extern s8 D_0047F810;
extern Mgr *D_00482388;
extern s32 D_00482FE0;
extern f32 D_00482FE4;
extern s8 D_00482FEC;
extern s16 D_00482FF0;
extern u8 D_004B2570[];

s32 MenuCatalogPageOpenState_35c820(s32 arg0, s32 arg1) {
    Ent *ent;
    s32 h;
    Spr *spr;
    f32 v;

    if (arg1 != 0) {
        D_00482FE0 = -1;
        D_0047F810 = 1;
        PadClearRepeatAll_183960(D_004B2570);
        PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
        PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
    }
    switch (D_00482FE0) {
    case -1:
        if (WorldDataMgrNoRequestPending_3eef10(((Ctx *)GetGameData_1fede0())->m8) != 0) {
            UiSetSpriteX_28fcd0(D_00482388->m274, 0x22, -6, 0);
            ent = ((Ent *)UiFindWidget_290460(D_00482388->m274, 0x1EE));
            if (ent == 0) {
                return 0;
            }
            h = ent->m20;
            if (h == 0) {
                return 0;
            }
            UiLayoutPanelFrame_28d580(h, 0, 0, 0x199, 0x152, 0);
            UiSetWidgetVisible_290010(D_00482388->m274, 0x1E9, 1, -1);
            UiSetWidgetPos_290f60(D_00482388->m274, 0x1E9, 0x200, 0x4C);
            UiMoveWidgetUniform_290f50(D_00482388->m274, 0x1E9, 0x52, 0x4C, D_0047D5C8, 0);
            UiFadeWidgetAlpha_290690(D_00482388->m274, 0x1E9, 1.0f, 0.0625f, 0.0f);
            UiSetWidgetVisible_290010(D_00482388->m274, 0x29, 1, -1);
            UiSetWidgetPos_290f60(D_00482388->m274, 0x29, 0x118, -0x19);
            UiMoveWidgetUniform_290f50(D_00482388->m274, 0x29, 0x118, 0xE, D_0047D5C8, 0);
            UiFadeWidgetAlpha_290690(D_00482388->m274, 0x29, 1.0f, 0.0625f, 0.0f);
            UiSlideInWidgetPair_28d010(0x1A, 0x11, D_00482388->m274);
            UiFadeWidgetAlpha_290690(D_00482388->m274, 0x41, 1.0f, D_0047D5E0, -1.0f);
            spr = ((Spr *)UiEntryListFindByTag_28ea40(D_00482388->m278, 0x24));
            spr->m16 = 0;
            spr->m1A = 0;
            D_00482FE0 = 0;
            D_00482FE4 = 0.0f;
            D_00482FEC = 0;
            D_00482FF0 = 0;
            MenuCatalogPageReset_360980(D_00482388);
            MenuCatalogTabSetup_360590(D_00482388);
            MenuCatalogTabSpritesUpdate_3603e0(D_00482388);
            UiSetWidgetsVisibleById_291110(D_00482388->m274, 0x1F6, 0, 1);
        }
        break;
    case 0:
        v = D_00482FE4 + D_0047D5EC;
        D_00482FE4 = v;
        if (!(v < D_0047D35C)) {
            D_00482FE4 = D_0047D35C;
            D_00482FE0 = 1;
        }
        break;
    case 1:
        D_00482FE4 -= D_0047D5EC;
        break;
    }
    if (D_00482FE4 <= 1.0f && D_00482FE0 == 1) {
        D_00482FE4 = 1.0f;
        StateMachineSetState_28ede0(D_00482388->m27C, 0xA4, 0);
    }
    UiSetWidgetColor_2905b0(D_00482388->m274, 0x41, D_00482FE4, D_00482FE4, D_00482FE4, 1.0f);
    return 1;
}
