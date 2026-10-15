#include "types.h"

typedef struct Chr {
    u8 pad0[0x24C];
    u8 flags;
} Chr;

typedef struct Ent {
    u8 pad0[0xC];
    u8 *unkC;
    u8 pad10[0x8];
    s32 unk18;
    u8 pad1C[0x4];
    Chr *unk20;
} Ent;

typedef struct Wnd {
    u8 pad0[0x4];
    u8 unk4[0xA];
    s16 unkE;
    u8 pad10[0x2];
    s16 unk12;
    s16 unk14;
    s16 unk16;
} Wnd;

typedef struct Game {
    u8 pad0[0x11];
    s8 unk11;
    u8 pad12[0x30];
    s16 unk42;
    u8 pad44[0x28];
    s32 unk6C;
    s16 unk70;
} Game;

typedef struct Sel {
    u8 pad0[0x10];
    s16 *unk10;
} Sel;

typedef struct Menu {
    u8 pad0[0x28];
    s16 *unk28;
} Menu;

extern Ent *GetGameData_1fede0(void);
extern Menu *GetWorldDataMgr_1fedf0(void);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern Wnd *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Wnd *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, u16, f32, f32, f32);
extern void MenuSetSelItem_2a02e0(Game *, Sel *);
extern s32 MenuWidgetIsDimmed_2a10f0(Game *, s32, s32);
extern void MenuItemCmdSetRowHighlight_2a1800(Game *, s32, s32, s32, s32);
extern Sel *MenuGetItemAtCell_2a7000(s32, void *);
extern void MenuWeaponCombineResultModelLoad_2a87c0(s32);
extern s32 NpcDataHeapCanAlloc_2b0990(void);
extern s32 LeaderRideObjIsStillMaybe_2f5270(void);
extern void MenuWeaponCombineUpdate_362920(s32, s32);
extern void PartyMenuCursorSet_3c0710(s32, s32, s16);
extern s32 PartyGetLocationGroupIdMaybe_3cb150(s32);
extern void WorldDataRequestKind_3f0960(Menu *, s32);
extern f32 D_0047D76C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Game *D_00482374;
extern s32 D_00482384;
extern s16 D_004823B0;
extern u8 D_004823CC;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;
extern u8 D_004B2570[0x400];

s32 MenuItemCommandSelectState_2b04e0(void *self, s32 init) {
    Wnd *w;
    s32 i;
    s32 r;
    Wnd *st;
    Ent *e;
    Sel *sel;
    s32 t;
    Menu *m;
    s32 k;

    if (init != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 4, 0);
        MenuItemCmdSetRowHighlight_2a1800(D_00482374, 0x7E, 0x7D, UiEntryListFindByTag_28ea40(D_00482364, 4)->unk16, D_00482374->unk42);
        w = UiEntryListFindByTag_28ea40(D_00482364, 4);
        if (w != 0) {
            for (i = 0; i < w->unkE + 1; i++) {
                UiFadeWidgetAlpha_290690(D_00482360, i + 0x83, 1.0f, D_0047D76C, -1.0f);
            }
        }
        D_004823B0 = 0;
        UiFadeWidgetAlpha_290690(D_00482360, 0x7E, 1.0f, D_0047D76C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x7D, 1.0f, D_0047D76C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A7, 1.0f, D_0047D76C, -1.0f);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 4, 0);
    st = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (D_004823CC != 0) {
        MenuWeaponCombineUpdate_362920(D_00482384, r);
    } else if (r == 1) {
        e = GetGameData_1fede0();
        sel = MenuGetItemAtCell_2a7000(D_00482374->unk11, UiEntryListFindByTag_28ea40(D_00482364, 3)->unk4);
        MenuSetSelItem_2a02e0(D_00482374, sel);
        t = D_00482374->unk42;
        if (MenuWidgetIsDimmed_2a10f0(D_00482374, 0x83, st->unk12) == 0) {
            StateMachineSetState_28ede0(D_0048235C, (u16)(st->unk12 + 0x2D), 0);
            if ((s16)t == 0 || (s16)t == 5) {
                if (st->unk12 == 2) {
                    m = GetWorldDataMgr_1fedf0();
                    if (*m->unk28 != 1) WorldDataRequestKind_3f0960(m, 1);
                }
            } else if ((s16)t == 3) {
                switch (st->unk12) {
                case 0:
                    if (!(e->unk20->flags & 1)) {
                        m = GetWorldDataMgr_1fedf0();
                        if (*m->unk28 != 3) WorldDataRequestKind_3f0960(m, 3);
                        MenuWeaponCombineResultModelLoad_2a87c0(1);
                    }
                    break;
                case 1:
                    if (!(e->unk20->flags & 1)) {
                        m = GetWorldDataMgr_1fedf0();
                        if (*m->unk28 != 3) WorldDataRequestKind_3f0960(m, 3);
                    }
                    break;
                }
            } else if ((s16)t == 4) {
                s32 v = st->unk12;
                if (v == 0) {
                    e = GetGameData_1fede0();
                    k = PartyGetLocationGroupIdMaybe_3cb150(e->unk18);
                    if (e->unk20->flags & 1) {
                        D_004823B0 = 0x3E8;
                        StateMachineSetState_28ede0(D_0048235C, 4, 0);
                    } else if (k == 1 || k == 10 || (u8)LeaderRideObjIsStillMaybe_2f5270() == 0) {
                        D_004823B0 = 0x3E9;
                        StateMachineSetState_28ede0(D_0048235C, 4, 0);
                    } else if (NpcDataHeapCanAlloc_2b0990() == 0) {
                        D_004823B0 = 0x3EA;
                        StateMachineSetState_28ede0(D_0048235C, 4, 0);
                    } else {
                        D_00482374->unk6C = *sel->unk10;
                        D_00482374->unk70 = 1;
                        w = UiEntryListFindByTag_28ea40(D_00482364, 3);
                        D_004824A0 = w->unk14;
                        D_004824A4 = w->unk16;
                        D_004824A8 = D_00482374->unk11;
                        e = GetGameData_1fede0();
                        if (*(s16 *)(e->unkC + 0x26) == 1) {
                            PartyMenuCursorSet_3c0710(e->unk18, 0, D_004824A0);
                            PartyMenuCursorSet_3c0710(e->unk18, 1, D_004824A4);
                            PartyMenuCursorSet_3c0710(e->unk18, 2, D_004824A8);
                        }
                        StateMachineSetState_28ede0(D_0048235C, 0x13, 1);
                    }
                } else if (v > 0 && v < 4) {
                    D_00482374->unk6C = *sel->unk10;
                }
            }
        }
    } else if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    }
    return 1;
}
