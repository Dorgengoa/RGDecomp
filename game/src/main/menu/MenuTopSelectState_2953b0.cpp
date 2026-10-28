/* rgp:protos */
#line 1
#include "types.h"

typedef struct Slot {
    u8 pad0[4];
    s16 m4;
    s16 m6;
    u8 pad8[2];
    s16 mA;
    u8 padC[2];
    s16 mE;
    u8 pad10[2];
    s16 m12;
    u8 pad14[2];
    s16 m16;
} Slot;

typedef struct Sub18 {
    u8 pad0[0x18E];
    s16 m18E;
} Sub18;

typedef struct Sub20 {
    u8 pad0[0x24C];
    u8 m24C;
} Sub20;

typedef struct Chr {
    u8 pad0[0x18];
    Sub18 *m18;
    u8 pad1C[4];
    Sub20 *m20;
} Chr;

typedef struct Sys {
    u8 pad0[0x28];
    s16 *m28;
} Sys;

extern "C" {
extern f32 Sinf_128fd0(f32);
extern s32 CharaIsNearLeaderMaybe_1fb230(s32, s32);
extern Chr *GetGameData_1fede0(void);
extern Sys *GetWorldDataMgr_1fedf0(void);
extern s32 IsTgsDemoBuild_207f20(void);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern Slot *UiEntryListFindByTag_28ea40(void *, s32);
extern void UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern Slot *UiEntryListGetCurrentData_28ec60(void *);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetSpriteSizeUvSize_28f670(void *, s32, s32, s32, s32, s32, s32);
extern void UiSetWidgetVisible_290010(void *, s32, s32, s32);
extern void UiSetWidgetColor_2905b0(void *, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void UiMoveWidgetUniform_290f50(void *, s32, s32, s32, f32, s32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void TopMenuLayoutEntries_294ad0(Slot *);
extern s32 TopMenuSelectFlashStep_295ec0(void);
extern void MenuShowPlayTime_298a40(s32);
extern void MenuMainResFree_298b60(void);
extern s32 TopMenuRow6UnlockedMaybe_29ac20(void);
extern s32 TopMenuRow5UnlockedMaybe_29ac50(void);
extern s32 TopMenuIsHunterUnlocked_29ac90(void);
extern void MenuHideAllPanels_29fc40(s32);
extern void MenuItemHideWidgets_2a5a60(s32);
extern void MenuCharaAbilityHideAllPanels_341160(s32);
extern void MenuTacticsHideAllPanels_357360(s32);
extern s32 SkillFlowHasLearnableMaybe_3e9580(Chr *, s32, int, int);
extern void RevelationBoardRefreshMaybe_3eaec0(Chr *, s32, s32);
extern s32 WorldDataMgrNoRequestPending_3eef10(Sys *);
extern void WorldDataRequestRelease_3f08f0(Sys *);
extern void WorldDataRequestKind_3f0960(Sys *, s32);
extern f32 D_0047D1FC;
extern f32 D_0047D344;
extern f32 D_0047D580;
extern f32 D_0047D5D0;
extern f32 D_0047D6CC;
extern f32 D_0047D7AC;
extern f32 D_0047D7BC;
extern s16 D_00482340;
extern s16 D_00482344;
extern s32 D_00482350;
extern s32 D_00482370;
extern s32 D_00482374;
extern s32 D_00482378;
extern s32 D_0048237C;
extern s16 D_0048239C;
extern s16 D_004823A0;
extern s16 D_004823AC;
extern s16 D_004823B0;
extern u8 D_004823E8;
extern u8 D_004823EC;
extern u8 D_004823F0;
extern f32 D_004823F4;
extern u8 D_0048241C;
extern u8 D_00482424;
extern u8 D_004B2570[];
extern u8 D_004DB1B0[];
extern u8 D_004DB1F0[];

#define UI D_004DB1B0
#define LIST D_004DB1F0

#define SYSSWITCH(sys)                      \
    switch (D_00482344) {                   \
    case 0:                                 \
    case 1:                                 \
    case 2:                                 \
    case 7:                                 \
        break;                              \
    case 3:                                 \
        WorldDataRequestKind_3f0960(sys, 1);               \
        break;                              \
    case 4:                                 \
        WorldDataRequestRelease_3f08f0(sys);                  \
        WorldDataRequestKind_3f0960(sys, 2);               \
        break;                              \
    case 5:                                 \
        WorldDataRequestRelease_3f08f0(sys);                  \
        WorldDataRequestKind_3f0960(sys, 3);               \
        break;                              \
    case 6:                                 \
        WorldDataRequestRelease_3f08f0(sys);                  \
        WorldDataRequestKind_3f0960(sys, 7);               \
        break;                              \
    }

#define GO27()                                               \
    UiSetWidgetColor_2905b0(UI, 0x27, 1.0f, 1.0f, 1.0f, 1.0f);          \
    UiFadeWidgetAlpha_290690(UI, 0x227, 0.0f, D_0047D7BC, -1.0f);

}
extern "C" s32 MenuTopSelectState_2953b0(s32 pad0, s32 arg1)
{
    s16 n;
    s32 i;
    s32 k;
    s32 r;
    s16 fl;
    s16 v;
    f32 f;
    f32 t;
    Slot *e;
    Slot *s;
    Sys *sys;
    Chr *c;
    bool ok;

    if (arg1 != 0 && D_004823A0 == 0 && D_00482340 != 7) {
        D_00482424 = 1;
        D_004823A0 = 0;
        UiSetWidgetsVisibleById_291110(UI, 0x227, 1, 1);
        n = D_00482344;
        if ((k = D_004823B0) != 0) {
            n = k;
        }
        if (D_0048239C != 0) {
            n = 6;
        }
        D_004823B0 = 0;
        UiEntryListSelectByTag_28ea90(LIST, 1, 0);
        e = UiEntryListFindByTag_28ea40(LIST, 1);
        if (D_0048241C != 0) {
            e->mE = 0;
        }
        UiSetWidgetPos_290f60(UI, 0x227, e->m4, e->m6 + n * e->mA);
        UiFadeWidgetAlpha_290690(UI, 0x227, 1.0f, D_0047D7AC, 0.0f);
        for (i = 0; i < 8; i++) {
            t = D_0047D580 * (f32)i; f = D_0047D344 - t;
            UiMoveWidgetUniform_290f50(UI, (u16)(i + 0x16), 0x21, i * 39 + 0x50, f, 0);
            UiMoveWidgetUniform_290f50(UI, (u16)(i + 0xD), 0x24, i * 39 + 0x53, f, 0);
            UiSetWidgetsVisibleById_291110(UI, (u16)(i + 0x1E), 1, 1);
        }
        e = UiEntryListGetCurrentData_28ec60(LIST);
        if (D_0048239C != 0) {
            e->m12 = 6;
        }
        k = e->m12;
        TopMenuLayoutEntries_294ad0(e);
        UiMoveWidgetUniform_290f50(UI, (u16)(k + 0x16), 0x2B, k * 39 + 0x50, D_0047D344, 0);
        UiMoveWidgetUniform_290f50(UI, (u16)(k + 0xD), 0x2E, k * 39 + 0x53, D_0047D344, 0);
        D_00482340 = 0;
        UiSetWidgetsVisibleById_291110(UI, 0x33, 1, 1);
        UiSetWidgetsVisibleById_291110(UI, 0x32, 1, 1);
        UiSetWidgetColor_2905b0(UI, 0x32, 0.0f, 0.0f, 0.0f, D_0047D6CC);
        UiMoveWidgetUniform_290f50(UI, 0x33, 0x9A, 0x12, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(UI, 0x32, 0x9D, 0x15, D_0047D5D0, 0);
        MenuItemHideWidgets_2a5a60(D_00482374);
        MenuHideAllPanels_29fc40(D_00482370);
        MenuCharaAbilityHideAllPanels_341160(D_00482378);
        MenuTacticsHideAllPanels_357360(D_0048237C);
        UiSetWidgetVisible_290010(UI, 0x1AD, 0, -1);
        UiSetWidgetVisible_290010(UI, 0x1B3, 0, -1);
        sys = GetWorldDataMgr_1fedf0();
        if (*sys->m28 != 1 && D_004823E8 == 0) {
            WorldDataRequestKind_3f0960(sys, 1);
            D_004823EC = 1;
        }
        if (SkillFlowHasLearnableMaybe_3e9580(GetGameData_1fede0(), -1, 0, 0) != 0) {
            D_004823F0 = 1;
        } else {
            D_004823F4 = 0.0f;
            D_004823F0 = 0;
        }
    }
    sys = GetWorldDataMgr_1fedf0();
    if (WorldDataMgrNoRequestPending_3eef10(sys) != 0 && D_004823EC != 0 && D_00482340 == 0 && D_004823E8 == 0) {
        c = GetGameData_1fede0();
        RevelationBoardRefreshMaybe_3eaec0(c, -1, 0);
        if (*sys->m28 == 1) {
            if (SkillFlowHasLearnableMaybe_3e9580(c, -1, 0, 0) != 0) {
                D_004823F0 = 1;
            } else {
                D_004823F4 = 0.0f;
                D_004823F0 = 0;
            }
            D_004823EC = 0;
        } else {
            WorldDataRequestKind_3f0960(sys, 1);
            D_004823EC = 1;
        }
    }
    if (D_004823F0 != 0) {
        f = D_004823F4 + D_0047D7AC;
        D_004823F4 = f;
        if (!(f < D_0047D1FC)) {
            D_004823F4 = 0.0f;
        }
        t = 1.0f + 0.5f * Sinf_128fd0(D_004823F4);
        UiSetWidgetColor_2905b0(UI, 0x21, t, t, t, -1.0f);
    } else {
        UiSetWidgetColor_2905b0(UI, 0x21, 1.0f, 1.0f, 1.0f, -1.0f);
    }
    if (D_00482340 == 0) {
        fl = 0;
        if (D_004823AC < 2) {
            fl = 0x10;
        }
        r = MenuGridCursorInput_28e170(LIST, D_004B2570, fl | 4, 0);
        s = UiEntryListFindByTag_28ea40(LIST, 1);
        if (D_004823AC == 2) {
            if (r == 1 || D_004823A0 != 0 || D_0048241C != 0) {
                D_0048239C = 0;
                c = GetGameData_1fede0();
                if (c == 0) {
                    return 0;
                }
                if (s->m16 == 7 && D_004823A0 == 0) {
                    D_00482344 = s->m16;
                    StateMachineSetState_28ede0((s32)&D_00482350, 5, 1);
                } else if (IsTgsDemoBuild_207f20() != 0) {
                    v = s->m16;
                    if (v < 4 || D_004823A0 != 0) {
                        D_00482344 = v;
                        sys = GetWorldDataMgr_1fedf0();
                        SYSSWITCH(sys)
                        D_00482340 = 1;
                        GO27()
                    }
                } else {
                    ok = true;
                    if (D_0048241C != 0) {
                        D_00482340 = 1;
                        D_00482344 = 0;
                        GO27()
                    } else {
                        k = s->m16;
                        if (k == 4) {
                            if (TopMenuIsHunterUnlocked_29ac90() == 0) {
                                ok = false;
                            }
                        } else if (k == 5) {
                            if (TopMenuRow5UnlockedMaybe_29ac50() == 0) {
                                ok = false;
                            }
                            if (ok && (c->m20->m24C & 1)) {
                                D_004823B0 = 5;
                                ok = false;
                                StateMachineSetState_28ede0((s32)&D_00482350, 4, 1);
                            }
                        } else if (k == 6) {
                            if (TopMenuRow6UnlockedMaybe_29ac20() == 0) {
                                ok = false;
                            }
                            if (ok && (c->m20->m24C & 1)) {
                                D_004823B0 = 6;
                                ok = false;
                                StateMachineSetState_28ede0((s32)&D_00482350, 4, 1);
                            } else if (ok && CharaIsNearLeaderMaybe_1fb230(c->m18->m18E, -1) == 0) {
                                D_004823B0 = 0x3E7;
                                ok = false;
                                StateMachineSetState_28ede0((s32)&D_00482350, 4, 1);
                            }
                        }
                        if (ok) {
                            D_00482344 = s->m16;
                            sys = GetWorldDataMgr_1fedf0();
                            SYSSWITCH(sys)
                            D_00482340 = 1;
                            GO27()
                        }
                    }
                }
            } else if (r == 2) {
                D_004823E8 = 1;
                MenuMainResFree_298b60();
                StateMachineSetState_28ede0((s32)&D_00482350, 3, 0);
            }
        }
    }
    TopMenuSelectFlashStep_295ec0();
    MenuShowPlayTime_298a40(0x35);
    if (D_00482340 == 7) {
        D_00482424 = 0;
        D_0048239C = 0;
        D_00482340 = 0;
        UiSetSpriteSizeUvSize_28f670(UI, (u16)(D_00482344 + 0x16), 0x74, 0x1A, 4, 4, 0);
        if ((v = D_004823A0) != 0) {
            if (D_004823AC == 2) {
                D_00482344 = 7;
                switch (v) {
                case 1:
                    StateMachineSetState_28ede0((s32)&D_00482350, 0x7F, 1);
                    break;
                case 2:
                    StateMachineSetState_28ede0((s32)&D_00482350, 0x82, 1);
                    break;
                }
                D_004823A0 = 0;
            }
        } else {
            switch (D_00482344) {
            case 0:
                StateMachineSetState_28ede0((s32)&D_00482350, 8, 1);
                break;
            case 1:
                StateMachineSetState_28ede0((s32)&D_00482350, 0x4A, 1);
                break;
            case 2:
                StateMachineSetState_28ede0((s32)&D_00482350, 0x95, 1);
                break;
            case 3:
                StateMachineSetState_28ede0((s32)&D_00482350, 0x6D, 1);
                break;
            case 4:
                StateMachineSetState_28ede0((s32)&D_00482350, 0xA3, 1);
                break;
            case 5:
                StateMachineSetState_28ede0((s32)&D_00482350, 0x8F, 1);
                break;
            case 6:
                UiEntryListSelectByTag_28ea90(LIST, 0x27, 0);
                break;
            case 7:
                break;
            }
        }
    }
    return 1;
}
