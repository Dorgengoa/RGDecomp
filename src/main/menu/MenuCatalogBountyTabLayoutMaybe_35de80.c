#include "types.h"

typedef struct Sub94 { u8 pad[0xC]; u8 *pC; } Sub94;
typedef struct L8 { u8 pad[0x94]; Sub94 *m94; } L8;
typedef struct Game { u8 pad[8]; L8 *m8; } Game;
typedef struct Mem {
    u8 pad0[0xE];
    s16 hE;
    u16 h10;
    u8 pad12[0xA];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 pad1D;
    s16 h1E;
} Mem;
typedef struct Elem { u8 pad0[4]; s16 m4; s16 m6; u8 pad8[2]; s16 mA; u8 padC[2]; s16 mE; u8 pad10[2]; s16 m12; s16 m14; s16 m16; s16 m18; s16 m1A; } Elem;
typedef struct Win {
    u8 pad0[0x1D0];
    f32 m1D0;
    u8 pad1D4[0x210 - 0x1D4];
    s32 m210;
    s32 m214;
    u8 pad218[0x228 - 0x218];
    s32 m228;
    s32 m22C;
    u8 pad230[0x24C - 0x230];
    s32 m24C;
    u8 pad250[0x274 - 0x250];
    s32 m274;
    s32 m278;
    u8 pad27C[0x288 - 0x27C];
    s32 m288;
    s32 m28C;
} Win;
typedef struct Iter { u8 d[8]; } Iter;

extern f32 D_0047D440;
extern s32 D_004823D8;
extern char D_004E8E50[][0x28];
extern char D_004E8F40[][4];

extern void *memset(void *, s32, u32);
extern Game *GetGameData_1fede0(void);
extern f32 UiPageScrollBarLayout_289710(Win *w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern Elem *UiEntryListFindByTag_28ea40(s32 h, s32 id);
extern void UiSetSubItemGlyphUvSize_28f100(s32 h, s32 id, s32 a, s32 b, s32 i);
extern void UiSetSubItemDigitCount_28f260(s32 h, s32 id, s32 a, s32 i);
extern void UiSetTextString_28f510(s32 h, s32 id, s32 s, s32 i);
extern void UiSetSpriteSizeUvSize_28f670(s32 h, s32 id, s32 a, s32 b, s32 c, s32 d, s32 i);
extern void UiSetWidgetAlpha_2907a0(s32 h, s32 id, f32 v);
extern void UiSetWidgetPos_290f60(s32 h, s32 id, s32 x, s32 y);
extern void UiSetWidgetsVisibleById_291110(s32 h, s32 id, s32 a, s32 b);
extern void UiSetWidgetSubItemValue_291250(s32 h, s32 id, s32 i, s32 v);
extern void MenuFormat3Digits_35cb40(Win *w, s32 v, s32 i);
extern void MenuCatalogBountyRowsFillMaybe_35cfe0(Win *w);
extern void MenuCatalogPlaceRowCursor_360350(Win *w);
extern Mem *IterNext_370040(Iter *);
extern void IterInit_370170(Iter *, u8 *);
extern void HunterBountyFormatLabel_3fdaf0(Mem *, char *);

void MenuCatalogBountyTabLayoutMaybe_35de80(Win *w)
{
    Iter it;
    Game *g;
    u8 *q;
    s32 i;
    s32 m;
    s32 n;
    s32 a;
    s32 b;
    Mem *e;
    s32 j;
    s32 sa;
    char *buf;
    s32 k;
    Elem *el;
    s32 save;

    w->m24C = 0;
    UiSetWidgetsVisibleById_291110(w->m274, 0x1F0, 1, 1);
    UiSetWidgetsVisibleById_291110(w->m274, 0x1F1, 1, 1);
    UiSetWidgetAlpha_2907a0(w->m274, 0x1F0, D_0047D440);
    UiSetWidgetAlpha_2907a0(w->m274, 0x1F1, D_0047D440);
    g = GetGameData_1fede0();
    q = g->m8->m94->pC;
    if (q != 0) {
        q += 0x88;
    }
    IterInit_370170(&it, q);
    for (i = 0; i < 6; i++) {
        memset(D_004E8E50[i], 0, 0x28);
        memset(D_004E8F40[i], 0, 4);
        UiSetWidgetSubItemValue_291250(w->m274, 0x209, i, 0);
        j = i * 2;
        UiSetSubItemDigitCount_28f260(w->m274, 0x20A, 2, j);
        m = (u32)i * 2;
        k = m + 1;
        UiSetSubItemDigitCount_28f260(w->m274, 0x20A, 2, k);
        UiSetWidgetSubItemValue_291250(w->m274, 0x20A, m, 0);
        UiSetWidgetSubItemValue_291250(w->m274, 0x20A, m + 1, 0);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x20A, 0xC, 0x10, 0xC, 0x10, j);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x20A, 0xC, 0x10, 0xC, 0x10, k);
        UiSetSubItemGlyphUvSize_28f100(w->m274, 0x20A, 0xC, 0x10, j);
        UiSetSubItemGlyphUvSize_28f100(w->m274, 0x20A, 0xC, 0x10, k);
        UiSetTextString_28f510(w->m274, 0x20C, MsgTableLookup_28aa30(D_004823D8, 0x1392), i);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x206, 0, 0, 0, 0, j);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x206, 0, 0, 0, 0, k);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x209, 0xC, 0x10, 0xC, 0x10, i);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x205, 0xE, 0x12, 0xE, 0x12, i);
        UiSetSubItemGlyphUvSize_28f100(w->m274, 0x209, 0xC, 0x10, i);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x1F0, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(w->m274, 0x1F1, 0, 0, 0, 0, i);
    }
    n = -1;
    while (e = IterNext_370040(&it), e != 0) {
        if (e->b0) {
            continue;
        }
        n++;
        if (n > 5) {
            continue;
        }
        MenuFormat3Digits_35cb40(w, n + 1, n);
        UiSetTextString_28f510(w->m274, 0x20B, (s32)D_004E8F40[n], n);
        if (!e->b1) {
            continue;
        }
        buf = D_004E8E50[n];
        HunterBountyFormatLabel_3fdaf0(e, buf);
        UiSetTextString_28f510(w->m274, 0x20C, (s32)buf, n);
        UiSetWidgetSubItemValue_291250(w->m274, 0x209, n, e->h10);
        a = e->h1E;
        if (a > 999) {
            a = 999;
        }
        b = e->hE;
        if (b > 99) {
            b = 99;
        }
        sa = (s16)a;
        j = n * 2;
        UiSetWidgetSubItemValue_291250(w->m274, 0x20A, j, sa);
        k = j + 1;
        UiSetWidgetSubItemValue_291250(w->m274, 0x20A, k, (s16)b);
        if ((s16)(s32)a >= 100) {
            UiSetSubItemDigitCount_28f260(w->m274, 0x20A, 3, (u32)n * 2);
        }
        if ((s16)(s32)b >= 100) {
            UiSetSubItemDigitCount_28f260(w->m274, 0x20A, 3, j + 1);
        }
        if (e->b3) {
            UiSetSubItemGlyphUvSize_28f100(w->m274, 0x209, 0, 0, n);
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x209, 0, 0, 0, 0, n);
            j = (s32)((u32)n * 2);
            UiSetWidgetSubItemValue_291250(w->m274, 0x20A, k, sa);
            UiSetSubItemDigitCount_28f260(w->m274, 0x20A, 3, j + 1);
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x205, 0, 0, 0, 0, n);
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x20A, 0, 0, 0, 0, j);
            UiSetSubItemGlyphUvSize_28f100(w->m274, 0x20A, 0, 0, j);
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x206, 0x3A, 0x20, 0x56, 0x30, j);
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x1F1, 0x150, 0x2A, 4, 4, n);
        } else if (e->b2) {
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x1F0, 0x150, 0x2A, 4, 4, n);
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x206, 0x3E, 0x1B, 0x56, 0x26, j + 1);
        }
    }
    w->m1D0 = 0.0f;
    w->m1D0 = UiPageScrollBarLayout_289710(w, 0x1F8, 0x116, 6, n + 1, 0);
    UiSetWidgetPos_290f60(w->m274, 0x1F8, 0x173, 0x1D);
    el = UiEntryListFindByTag_28ea40(w->m278, 0x24);
    el->m12 = n;
    el->m14 = w->m210;
    el->m16 = w->m214;
    el->m18 = w->m228;
    el->m1A = w->m22C;
    w->m288 = w->m214;
    w->m28C = w->m22C;
    UiSetWidgetPos_290f60(w->m274, 0x1F8, 0x173, (s32)(29.0f + (f32)el->m1A * w->m1D0));
    UiSetWidgetPos_290f60(w->m274, 0x20E, el->m4, el->m6 + el->m16 * el->mA);
    MenuCatalogPlaceRowCursor_360350(w);
    save = el->m16;
    el->m16 = el->mE;
    MenuCatalogBountyRowsFillMaybe_35cfe0(w);
    el->m16 = save;
}
