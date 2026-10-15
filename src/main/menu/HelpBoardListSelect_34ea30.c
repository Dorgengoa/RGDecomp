#include "types.h"

typedef struct T {
    u8 pad0[2];
    s16 s2;     /* 02 */
    u8 pad4[2];
    s16 s6;     /* 06 */
    u8 pad8[2];
    s16 sA;     /* 0A */
    u8 padC[2];
    s16 sE;     /* 0E */
    u8 pad10[2];
    s16 s12;    /* 12 */
    u8 pad14[2];
    s16 s16;    /* 16 */
    u8 pad18[2];
    s16 s1A;    /* 1A */
} T;
typedef struct M { u8 pad[0x14]; s32 i14; } M;
typedef struct G2 { u8 pad[0x26]; s16 s26; } G2;
typedef struct G { u8 pad[0xC]; G2 *p0C; u8 pad10[8]; s32 i18; } G;

void MemStackReset_14d830(s32);
void NameTableFreeGroup_158ac0(s32, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsRepeatTriggered_183dd0(void *, s32);
G *GetGameData_1fede0(void);
void PlayMenuSe_289ef0(s32);
s32 MenuGridCursorInput_28e170(M *, void *, s32, s32);
void MenuGridCursorRequestSe_28e9e0(M *, s32);
T *UiEntryListFindByTag_28ea40(M *, s32);
void UiEntryListSelectByTag_28ea90(M *, s32, s32);
T *UiEntryListGetCurrentData_28ec60(M *);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void MenuResRelease_299280(void);
void HelpBoardLoadSelected_34daa0(void);
void HelpBoardFillList_34dc90(s32);
void HelpBoardDebugUnlockAll_34f060(void);
void PartyMenuCursorSet_3c0710(s32, s32, s32);
extern f32 D_0047D634;
extern u8 D_0047F6E8;
extern s16 D_0047F6F0;
extern s32 D_00482338;
extern s32 D_0048235C;
extern s32 D_00482360;
extern M *D_00482364;
extern s16 D_00482E86;
extern f32 D_00482E88;
extern s32 D_00482EAC;
extern s16 D_00482EB4;
extern u8 D_00482EB8;
extern u8 D_004B2570[];

s32 HelpBoardListSelect_34ea30(s32 pad0, s32 init) {
    s32 r;
    T *t;
    G *g;
    s32 a;

    if (init) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1E, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x219, 1.0f, D_0047D634, -1.0f);
        HelpBoardFillList_34dc90(UiEntryListFindByTag_28ea40(D_00482364, 0x1E)->s1A);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    t = UiEntryListGetCurrentData_28ec60(D_00482364);
    HelpBoardDebugUnlockAll_34f060();
    if (r == 1) {
        if (UiGetWidgetAlpha_290770(D_00482360, 0x219) == 0.0f) return 1;
        if (D_00482EB8 == 0) {
            MenuResRelease_299280();
            D_00482EB8 = 1;
        }
        D_0047F6F0 = 1;
        HelpBoardLoadSelected_34daa0();
        PlayMenuSe_289ef0(0x2D);
        StateMachineSetState_28ede0(D_0048235C, 0x86, 0);
    } else if (r == 2) {
        D_00482EAC = 0;
        D_00482EB4 = t->s12 + t->s16;
        g = GetGameData_1fede0();
        if (g->p0C->s26 == 1) {
            PartyMenuCursorSet_3c0710(g->i18, 0x14, D_00482EB4);
        }
        D_0047F6E8 = 0;
        if (D_00482EB8 != 0) {
            NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32E);
            MemStackReset_14d830(D_00482338);
        } else {
            D_0047F6E8 = 1;
        }
        StateMachineSetState_28ede0(D_0048235C, 0x84, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
        if (t->s12 > 0 || t->s16 > 0) MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        if (t->s16 > 0) {
            t->s16 = t->s16 - (s16)(t->sA + 1);
            if (t->s16 < 0) {
                t->s16 = 0;
                t->s12 = 0;
                UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, t->s2, 0);
            }
            HelpBoardFillList_34dc90(t->s16);
        } else {
            t->s16 = 0;
            t->s12 = 0;
            UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, t->s2, 0);
        }
        if (t->s16 < 0) t->s16 = 0;
        UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)t->s16 * D_00482E88), 0, D_0047D634);
        D_00482E86 = t->s12;
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
        if (t->s12 < t->sA || t->s16 < t->sE - t->sA) MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        a = t->sA;
        if (t->s16 < t->sE - a) {
            t->s16 = t->s16 + (s16)(a + 1);
            if (t->s16 > t->sE - t->sA) {
                t->s12 = t->sA;
                t->s16 = t->sE - t->sA;
                UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, t->s2 + t->s12 * t->s6, 0);
            }
            HelpBoardFillList_34dc90(t->s16);
        } else {
            t->s12 = a;
            t->s16 = t->sE - t->sA;
            UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, t->s2 + t->s12 * t->s6, 0);
        }
        if (t->s16 < 0) t->s16 = 0;
        UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)t->s16 * D_00482E88), 0, D_0047D634);
        D_00482E86 = t->s12;
    } else if ((D_00482364->i14 & 1) && PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000) == 0) {
        if (t->s12 == 0 && t->s16 == 0 && t->sE > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
            t->s12 = t->sA;
            t->s16 = t->sE - t->sA;
            UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, t->s2 + t->s12 * t->s6, 0);
            HelpBoardFillList_34dc90(t->s16);
            UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, (s32)((f32)t->s16 * D_00482E88));
            D_00482E86 = t->s12;
            if (t->s16 < 0) t->s16 = 0;
        }
    } else if ((D_00482364->i14 & 2) && PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000) == 0) {
        if (t->s12 == t->sA && t->s16 == t->sE - t->sA && t->sE > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
            t->s12 = 0;
            t->s16 = 0;
            UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, t->s2 + t->s12 * t->s6, 0);
            HelpBoardFillList_34dc90(t->s16);
            UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, (s32)((f32)t->s16 * D_00482E88));
            D_00482E86 = t->s12;
            if (t->s16 < 0) t->s16 = 0;
        }
    }
    return 1;
}
