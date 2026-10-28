/* rgp:protos */
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct { s16 f0; s16 f2; s16 f4; s16 f6; s16 f8; s16 fA; s16 fC; s16 fE; s16 f10; s16 f12; s16 f14; s16 f16; } Sub;
typedef struct { s16 f0; s16 f2; s16 f4; s16 f6; s16 f8; s16 fA; s16 fC; s16 fE; s16 f10; s16 f12; s16 f14; s16 f16; s16 f18; s16 f1A; } Ent;

extern "C" {
extern u8 *GetGameData_1fede0(void);
extern s32 PadIsTriggered_1839f0(u8 *, s32);
extern s32 PadIsRepeatTriggered_183dd0(u8 *, s32);
extern void PlayMenuSe_289ef0(s32);
extern s32 MenuGridCursorInput_28e170(s32, u8 *, s16, s32);
extern void MenuGridCursorRequestSe_28e9e0(s32, s32);
extern Ent *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Sub *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuModelPageSaveCursor_358f10(u8 *);
extern void MenuModelPageSetSelectionMaybe_359060(u8 *, s32, s32, Ent *);
extern void MenuModelPageCharaLabelLayoutMaybe_359120(u8 *);
extern void MenuModelPageTabSpritesUpdate_3593e0(u8 *);
extern void MenuModelPageShowCursorEntryItemsMaybe_359cf0(u8 *);
extern void MenuModelPageLogRowsRefreshMaybe_35a1a0(u8 *);
extern void MenuModelPageShowFirstEntryItemsMaybe_35a6b0(u8 *);
extern void MenuModelPageLogListLayoutMaybe_35aaf0(u8 *);
extern void MenuCursorBobUpdate_35b1b0(u8 *, s32);
extern u8 D_004B2570[];
extern f32 D_0047D61C;
extern u8 *D_00482380;
extern s32 D_00482F88;
extern s32 D_00482F8C;
}

#define G134 (*(s32 *)(D_00482380 + 0x134))
#define G138 (*(s32 *)(D_00482380 + 0x138))
#define G13C (*(s32 *)(D_00482380 + 0x13C))
#define G64 (*(f32 *)(D_00482380 + 0x64))

extern "C" s32 MenuModelPageSelectState_3575d0(s32 a0, s32 init) {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 k;
    Sub *s;
    Ent *e;
    s32 i;
    s32 t;
    s32 n;
    f32 fc;
    f32 fg;

    if (init) {
        UiEntryListSelectByTag_28ea90(G138, 0x28, 0);
    }
    GetGameData_1fede0();
    t = 0;
    if (D_00482380[0x16C] == 0) {
        t = 4;
    }
    n = G138;
    k = MenuGridCursorInput_28e170(n, D_004B2570, t, 0);
    s = UiEntryListGetCurrentData_28ec60(G138);
    if (D_00482380[0x16C] == 0) {
        if (k == 2) {
            e = UiEntryListFindByTag_28ea40(G138, 0x28);
            i = e->f1A + e->f16;
            MenuModelPageSetSelectionMaybe_359060(D_00482380, i, D_00482380[0x16D + i], 0);
            MenuModelPageSaveCursor_358f10(D_00482380);
            StateMachineSetState_28ede0(G13C, 0x91, 0);
        } else if (k == 1) {
            MenuModelPageSetSelectionMaybe_359060(D_00482380, D_00482380[0x175], D_00482380[0x16D + D_00482380[0x175]], 0);
            UiEntryListSelectByTag_28ea90(G138, 0x20, 0);
            D_00482380[0x16C] = 1;
            UiSetWidgetsVisibleById_291110(G134, 0x1DE, 1, 1);
            UiSetWidgetsVisibleById_291110(G134, 0x24A, 1, 1);
            UiSetWidgetVisible_290010(G134, 0x1D1, 1, -1);
            UiSetWidgetPos_290f60(G134, 0x1D1, 0x200, 0x47);
            UiMoveWidgetUniform_290f50(G134, 0x1D1, 0x70, 0x47, D_0047D61C, 0);
            UiFadeWidgetAlpha_290690(G134, 0x1D1, 1.0f, 0.0625f, 0.0f);
            UiFadeWidgetAlpha_290690(G134, 0x1DE, 1.0f, 0.0625f, 0.0f);
            UiGetWidgetPos_2910a0(G134, 0x23A, &x0, &y0);
            UiMoveWidgetUniform_290f50(G134, 0x23A, 0x200, y0, D_0047D61C, 0);
            UiFadeWidgetAlpha_290690(G134, 0x23A, 0.0f, 0.0625f, -1.0f);
            UiSetWidgetPos_290f60(G134, 0x24A, 0, -0x32);
            UiMoveWidgetUniform_290f50(G134, 0x24A, 0, 0, 0.25f, 0);
            UiFadeWidgetAlpha_290690(G134, 0x24A, 1.0f, 0.0625f, 0.0f);
            UiFadeWidgetAlpha_290690(G134, 0x246, 0.0f, 0.0625f, -1.0f);
            MenuCursorBobUpdate_35b1b0(D_00482380, 1);
            D_00482380[0x175] = UiEntryListFindByTag_28ea40(G138, 0x28)->f16;
            MenuModelPageCharaLabelLayoutMaybe_359120(D_00482380);
            MenuModelPageTabSpritesUpdate_3593e0(D_00482380);
            e = UiEntryListFindByTag_28ea40(G138, 0x20);
            e->f16 = 0;
            e->f1A = 0;
            UiSetWidgetPos_290f60(G134, 0x1E4, e->f4, e->f6);
            UiSetWidgetVisible_290010(G134, 0x1D2, 1, -1);
            UiFadeWidgetAlpha_290690(G134, 0x1D2, 1.0f, 0.0625f, 0.0f);
            MenuModelPageLogListLayoutMaybe_35aaf0(D_00482380);
            MenuModelPageShowFirstEntryItemsMaybe_35a6b0(D_00482380);
            UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, e->f16 * e->fA + 0x11);
            MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
            MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
            UiSetWidgetPos_290f60(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)e->f1A, (s32)(30.0f + fc * fg)));
            if (e->f1A < 0) {
                e->f1A = 0;
            }
        }
    } else if (D_00482380[0x16C] == 1) {
    if (k == 2) {
        e = UiEntryListFindByTag_28ea40(G138, 0x20);
        MenuModelPageSetSelectionMaybe_359060(D_00482380, D_00482380[0x175], D_00482380[0x16D + D_00482380[0x175]], e);
        UiEntryListSelectByTag_28ea90(G138, 0x28, 0);
        D_00482380[0x16C] = 0;
        UiGetWidgetPos_2910a0(G134, 0x23A, &x1, &y1);
        UiMoveWidgetUniform_290f50(G134, 0x23A, 0x60, y1, D_0047D61C, 0);
        UiFadeWidgetAlpha_290690(G134, 0x23A, 1.0f, 0.0625f, -1.0f);
        UiMoveWidgetUniform_290f50(G134, 0x1D1, 0x200, 0x47, D_0047D61C, 0);
        UiFadeWidgetAlpha_290690(G134, 0x1D1, 0.0f, 0.0625f, -1.0f);
        UiFadeWidgetAlpha_290690(G134, 0x1DE, 0.0f, 0.0625f, -1.0f);
        UiMoveWidgetUniform_290f50(G134, 0x24A, 0, -0x32, 0.25f, 0);
        UiFadeWidgetAlpha_290690(G134, 0x24A, 0.0f, 0.0625f, -1.0f);
        UiFadeWidgetAlpha_290690(G134, 0x246, 1.0f, 0.0625f, -1.0f);
        UiFadeWidgetAlpha_290690(G134, 0x1D2, 0.0f, 0.0625f, -1.0f);
        e = UiEntryListFindByTag_28ea40(G138, 0x28);
        e->f16 = D_00482380[0x175];
        MenuCursorBobUpdate_35b1b0(D_00482380, 1);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000)) {
        if (s->f12 > 0 || s->f16 > 0) {
            MenuGridCursorRequestSe_28e9e0(G138, 0);
        }
        if (s->f16 > 0) {
            s->f16 = s->f16 - (s16)(s->fA + 1);
            if (s->f16 < 0) {
                s->f16 = 0;
                s->f12 = 0;
                UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, 0x11);
            }
            MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
        } else {
            s->f16 = 0;
            s->f12 = 0;
            UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, 0x11);
        }
        if (s->f16 < 0) {
            s->f16 = 0;
        }
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
        UiMoveWidgetUniform_290f50(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)), 0.25f, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000)) {
        if (s->f12 < s->fA || s->f16 < s->fE - s->fA) {
            MenuGridCursorRequestSe_28e9e0(G138, 0);
        }
        if (s->f16 < s->fE - s->fA) {
            s->f16 = s->f16 + (s16)(s->fA + 1);
            if (s->f16 > s->fE - s->fA) {
                s->f12 = s->fA;
                s->f16 = s->fE - s->fA;
                UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
            }
            MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
        } else {
            s->f12 = s->fA;
            s->f16 = s->fE - s->fA;
            UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
        }
        if (s->f16 < 0) {
            s->f16 = 0;
        }
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
        UiMoveWidgetUniform_290f50(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)), 0.25f, 0);
    } else if ((*(s32 *)(G138 + 0x14) & 1) && PadIsTriggered_1839f0(D_004B2570, 0x1000) && !PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000)) {
        if (s->f12 == 0 && s->f16 == 0 && s->fE > 0) {
            MenuGridCursorRequestSe_28e9e0(G138, 0);
            s->f12 = s->fA;
            s->f16 = s->fE - s->fA;
            UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
            MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
            MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
            UiSetWidgetPos_290f60(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)));
            if (s->f16 < 0) {
                s->f16 = 0;
            }
        }
    } else if ((*(s32 *)(G138 + 0x14) & 2) && PadIsTriggered_1839f0(D_004B2570, 0x4000) && !PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000)) {
        if (s->f12 == s->fA && s->f16 == s->fE - s->fA && s->fE > 0) {
            MenuGridCursorRequestSe_28e9e0(G138, 0);
            s->f12 = 0;
            s->f16 = 0;
            UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
            MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
            MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
            UiSetWidgetPos_290f60(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)));
            if (s->f16 < 0) {
                s->f16 = 0;
            }
        }
    }
    e = UiEntryListFindByTag_28ea40(G138, 0x20);
    if (PadIsTriggered_1839f0(D_004B2570, 0xC)) {
        PlayMenuSe_289ef0(0xB);
        t = D_00482380[0x16D + D_00482380[0x175]] ^ 1;
        MenuModelPageSetSelectionMaybe_359060(D_00482380, D_00482380[0x175], t, e);
        D_00482380[0x16D + D_00482380[0x175]] = t;
        MenuModelPageTabSpritesUpdate_3593e0(D_00482380);
        e->f16 = 0;
        e->f1A = 0;
        MenuModelPageLogListLayoutMaybe_35aaf0(D_00482380);
        MenuModelPageShowFirstEntryItemsMaybe_35a6b0(D_00482380);
        UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
        MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
        UiSetWidgetPos_290f60(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)));
        if (s->f16 < 0) {
            s->f16 = 0;
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 1)) {
        PlayMenuSe_289ef0(0xB);
        n = (s8)D_00482380[0xD8];
        i = (D_00482380[0x175] + (n - 1)) % n;
        MenuModelPageSetSelectionMaybe_359060(D_00482380, i, D_00482380[0x16D + i], e);
        D_00482380[0x175] = i;
        MenuModelPageCharaLabelLayoutMaybe_359120(D_00482380);
        MenuModelPageTabSpritesUpdate_3593e0(D_00482380);
        e->f16 = 0;
        e->f1A = 0;
        MenuModelPageLogListLayoutMaybe_35aaf0(D_00482380);
        MenuModelPageShowFirstEntryItemsMaybe_35a6b0(D_00482380);
        UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
        MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
        UiSetWidgetPos_290f60(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)));
        if (s->f16 < 0) {
            s->f16 = 0;
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 2)) {
        PlayMenuSe_289ef0(0xB);
        n = (s8)D_00482380[0xD8];
        i = (D_00482380[0x175] + 1) % n;
        MenuModelPageSetSelectionMaybe_359060(D_00482380, i, D_00482380[0x16D + i], e);
        D_00482380[0x175] = i;
        MenuModelPageCharaLabelLayoutMaybe_359120(D_00482380);
        MenuModelPageTabSpritesUpdate_3593e0(D_00482380);
        e->f16 = 0;
        e->f1A = 0;
        MenuModelPageLogListLayoutMaybe_35aaf0(D_00482380);
        MenuModelPageShowFirstEntryItemsMaybe_35a6b0(D_00482380);
        UiSetWidgetPos_290f60(G134, 0x1DE, 0x10, s->f12 * s->f6 + 0x11);
        MenuModelPageLogRowsRefreshMaybe_35a1a0(D_00482380);
        MenuModelPageShowCursorEntryItemsMaybe_359cf0(D_00482380);
        UiSetWidgetPos_290f60(G134, 0x1D9, 0x14D, (fg = G64, fc = (f32)s->f16, (s32)(30.0f + fc * fg)));
        if (s->f16 < 0) {
            s->f16 = 0;
        }
    }
    D_00482F88 = s->f12;
    D_00482F8C = s->f16;
    }
    return 1;
}
