#pragma optimization_level 3
#include "types.h"
#pragma opt_propagation off
#pragma opt_loop_invariants off

typedef struct T9 { s32 v[9]; } T9;
typedef struct H9 { s16 v[9]; } H9;

extern u8 *GetGameData_1fede0();
extern s32 MsgTableLookup_28aa30(s32, s32);
extern u8 *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiSetSubItemGlyphUvSize_28f100(s32, s32, s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiSetSpriteScaleY_28fa70(s32, s32, s32, s32);
extern void UiSetSpriteH_28fbb0(s32, s32, s32, s32);
extern void UiSetSpriteY_28fc90(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSetWidgetSubItemValue_291250(s32, s32, s32, s32);
extern void MenuModelPageTextBoxFitWidthMaybe_359590(u8 *, s32);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyFindSlotOfId_3c3070(s32, s32);
extern void PartyCharaWeaponCombineTallyMaybe_3e93a0(u8 *);
extern s32 D_00453D80[];
extern s16 D_00453DB0[];
extern u8 D_00462C10[];
extern f32 D_0047D61C;
extern s32 D_004823D8;

#define W (*(s32 *)(self + 0x134))
#define CNT (*(s8 *)(self + 0xD8))
#define SLOT(i) (*(s16 *)(self + 0xDA + (i) * 2))

void MenuModelPageCharaInfoLayoutMaybe_359700(u8 *self) {
    u8 *g; u8 *g2; u8 *e; u8 *tb; u8 *rec; u8 *ps; s32 h; s32 a; s32 i; s32 j; s32 m; s32 q; s32 c; s32 c1; s32 x0; s32 x1; s32 v; s32 y; s32 z; s8 n; s8 k; s32 ids[9]; s16 sl[9];

    g = GetGameData_1fede0();
    { s32 one = 1; UiSetWidgetsVisibleById_291110(W, 0x23A, one, one); }
    UiSetWidgetsVisibleById_291110(W, 0x246, 0, 1);
    i = 0;
    do {
        UiSetWidgetsVisibleById_291110(W, (u16)(i + 0x23B), 0, 1);
        UiSetSubItemGlyphUvSize_28f100(W, 0x24C, 0, 0, i * 2);
        UiSetSubItemGlyphUvSize_28f100(W, 0x24C, 0, 0, (s32)((u32)i * 2) + 1);
        i++;
    } while (i < 8);
    CNT = 0;
    h = *(s32 *)(g + 0x18);
    { s32 one = 1; a = PartyCountMembers_3c2010(h, one, one); }
    { s32 one = 1; n = a + PartyCountReserve_3c1c20(h, one, one); }
    CNT = n;
    UiSetSpriteScaleY_28fa70(W, 0x23A, n - 1, 9);
    UiSetSpriteScaleY_28fa70(W, 0x23A, CNT - 1, 0x13);
    i = 0;
    do {
        UiSetSpriteScaleY_28fa70(W, 0x245, CNT, i);
        i++;
    } while (i < 3);
    i = 0;
    do {
        { s32 o = i * 2; s32 c5 = 0x23A; UiSetTextString_28f510(W, c5, (s32)D_00462C10, o); }
        { s32 o = (s32)((u32)i * 2) + 1; s32 w = W; s32 c5 = 0x23A; UiSetTextString_28f510(w, c5, (u32)D_00462C10, o); }
        i++;
    } while (i < 8);
    for (j = 0; j < CNT; j++) {
        x0 = j * 2;
        UiSetTextString_28f510(W, 0x23A, MsgTableLookup_28aa30(D_004823D8, 0x1770), x0);
        x1 = (s32)((u32)j * 2) + 1;
        UiSetTextString_28f510(W, 0x23A, MsgTableLookup_28aa30(D_004823D8, 0x1771), x1);
        UiSetSubItemGlyphUvSize_28f100(W, 0x24C, 0xC, 0x10, x0);
        UiSetSubItemGlyphUvSize_28f100(W, 0x24C, 0xC, 0x10, x1);
    }
    MenuModelPageTextBoxFitWidthMaybe_359590(self, MsgTableLookup_28aa30(D_004823D8, 0x1772));
    UiSetTextString_28f510(W, 0x24A, MsgTableLookup_28aa30(D_004823D8, 0x1773), 0);
    y = CNT * 27 - 8;
    UiSetSpriteH_28fbb0(W, 0x23A, y + 8, 0);
    UiSetSpriteH_28fbb0(W, 0x23A, y, 4);
    UiSetSpriteH_28fbb0(W, 0x23A, y, 5);
    UiSetSpriteY_28fc90(W, 0x23A, y + 8, 6);
    UiSetSpriteY_28fc90(W, 0x23A, y + 8, 7);
    UiSetSpriteY_28fc90(W, 0x23A, y + 8, 8);
    UiSetSpriteH_28fbb0(W, 0x23A, y + 8, 0xA);
    UiSetSpriteH_28fbb0(W, 0x23A, y, 0xE);
    UiSetSpriteH_28fbb0(W, 0x23A, y, 0xF);
    UiSetSpriteY_28fc90(W, 0x23A, y + 8, 0x10);
    UiSetSpriteY_28fc90(W, 0x23A, y + 8, 0x11);
    UiSetSpriteY_28fc90(W, 0x23A, y + 8, 0x12);
    y = 0x12C - (y + 0x10);
    UiSetWidgetPos_290f60(W, 0x23A, 0x200, y);
    *(T9 *)ids = *(T9 *)D_00453D80;
    *(H9 *)sl = *(H9 *)D_00453DB0;
    k = 0;
    i = 0;
    do {
        z = i * 2;
        *(s16 *)(self + 0xDA + z) = -1;
        if (PartyFindSlotOfId_3c3070(*(s32 *)(g + 0x18), *(s32 *)((u32)&ids[i])) < 0) continue;
        { s32 kk = k;
        SLOT(kk) = *(s16 *)((u8 *)sl + z);
        z = *(s32 *)((u32)&ids[(u32)i]) + 0x23B;
        UiSetWidgetPos_290f60(W, (u16)z, 7, kk * 27 + 7); }
        { s32 one = 1; UiSetWidgetsVisibleById_291110(W, (u16)(u32)z, one, one); }
        k++;
    } while (++i, i < 8);
    UiMoveWidgetUniform_290f50(W, 0x23A, 0x60, y, 0, D_0047D61C);
    UiFadeWidgetAlpha_290690(W, 0x23A, 1.0f, 0.0625f, 0.0f);
    e = UiEntryListFindByTag_28ea40(*(s32 *)(self + 0x138), 0x28);
    UiSetWidgetPos_290f60(W, 0x243, *(s16 *)(e + 4), *(s16 *)(e + 6));
    *(s16 *)(e + 0x16) = 0;
    *(s16 *)(e + 0x1A) = 0;
    *(s16 *)(e + 0xE) = CNT - 1;
    g2 = GetGameData_1fede0();
    PartyCharaWeaponCombineTallyMaybe_3e93a0(g2);
    tb = *(u8 **)(*(u8 **)(*(u8 **)(g2 + 8) + 0x90) + 0x10);
    for (m = 0; m < 8; m++) {
        c = m * 2;
        ps = self + c;
        if (*(s16 *)(ps + 0xDA) == -1) return;
        q = 0;
        c1 = c + 1;
        do {
            rec = tb + q * 6;
            if (*(s16 *)(ps + 0xDA) != *(s16 *)rec) continue;
            UiSetWidgetSubItemValue_291250(W, 0x24C, c, rec[4]);
            UiSetWidgetSubItemValue_291250(W, 0x24C, c1, rec[3]);
        } while (++q, q < 8);
    }
}
