/* rgp:protos */
#define RGP_SELF_MenuCatalogBountyRowsFillMaybe_35cfe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad[0x1C];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
} Unk;

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
extern void *memset(void *, s32, u32);
extern s32 D_004823D8;
extern u8 D_004E8E50[0x400];
extern u8 D_004E8F40[0x400];

#define W (*(volatile s32 *)(arg0 + 0x274))

void MenuCatalogBountyRowsFillMaybe_35cfe0(s8 *arg0) {
    s8 *d;
    u64 bits;
    s32 lim;
    s32 cy;
    s32 h;
    s32 lv;
    s32 i;
    s32 hp;
    s32 t;
    s32 cx;
    s8 *p;
    s32 it[2];
    s32 j;
    s32 k;
    s32 lst;
    s32 j2;
    s8 *hdr;

    lst = *(s32 *)(*(s8 **)(*(s8 **)(((s8 *)GetGameData_1fede0()) + 8) + 0x94) + 0xC);
    if (lst != 0) {
        lst += 0x88;
    }
    IterInit_370170(it, lst, 0, 0);
    hdr = ((s8 *)UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 0x278), 0x24));
    t = *(s16 *)(hdr + 0x16);
    k = 0;
    lim = t + *(s16 *)(hdr + 0x1A);
    if (t == 5) {
        lim -= 5;
    }
    while (k < lim) {
        p = ((s8 *)IterNext_370040(it));
        if (p == NULL || !(*(u8 *)(p + 0x1C) & 1)) {
            k++;
        }
    }
    lv = 0;
    do {
        memset(D_004E8E50 + lv * 0x28, 0, 0x28);
        memset(D_004E8F40 + lv * 4, 0, 4);
        UiSetWidgetSubItemValue_291250(W, 0x209, lv, (long long)(0));
        UiSetSubItemDigitCount_28f260(W, 0x20A, 2, lv * 2);
        UiSetSubItemDigitCount_28f260(W, 0x20A, 2, (u32)lv * 2 + 1);
        UiSetWidgetSubItemValue_291250(W, 0x20A, (u32)lv * 2, (long long)(0));
        UiSetWidgetSubItemValue_291250(W, 0x20A, (s32)((u32)lv * 2) + 1, (long long)(0));
        cx = 0xC; cy = 0x10;
        UiSetSpriteSizeUvSize_28f670(W, 0x20A, cx, cy, cx, cy, lv * 2);
        cx = 0xC; cy = 0x10;
        UiSetSpriteSizeUvSize_28f670(W, 0x20A, cx, cy, cx, cy, (u32)lv * 2 + 1);
        UiSetSubItemGlyphUvSize_28f100(W, 0x20A, 0xC, 0x10, lv * 2);
        UiSetSubItemGlyphUvSize_28f100(W, 0x20A, 0xC, 0x10, (u32)lv * 2 + 1);
        UiSetTextString_28f510(W, 0x20C, MsgTableLookup_28aa30(D_004823D8, 0x1392), lv);
        UiSetSpriteSizeUvSize_28f670(W, 0x206, 0, 0, 0, 0, lv * 2);
        UiSetSpriteSizeUvSize_28f670(W, 0x206, 0, 0, 0, 0, (u32)lv * 2 + 1);
        cx = 0xC; cy = 0x10;
        UiSetSpriteSizeUvSize_28f670(W, 0x209, cx, cy, cx, cy, lv);
        cx = 0xE; cy = 0x12;
        UiSetSpriteSizeUvSize_28f670(W, 0x205, cx, cy, cx, cy, lv);
        UiSetSubItemGlyphUvSize_28f100(W, 0x209, 0xC, 0x10, lv);
        UiSetSpriteSizeUvSize_28f670(W, 0x1F0, 0, 0, 0, 0, lv);
        UiSetSpriteSizeUvSize_28f670(W, 0x1F1, 0, 0, 0, 0, lv);
        lv++;
    } while (lv < 6);
    i = -1;
    while (p = ((s8 *)IterNext_370040(it)), p != NULL) {
        if (*(u8 *)(p + 0x1C) & 1) {
            continue;
        }
        i++;
        if (i >= 6) {
            return;
        }
        MenuFormat3Digits_35cb40(arg0, i + lim + 1, i);
        { s32 q = (s32)(D_004E8F40 + i * 4); UiSetTextString_28f510(W, 0x20B, q, i); }
        if (!((Unk *)p)->b1) {
            continue;
        }
        d = (s8 *)(D_004E8E50 + i * 0x28);
        HunterBountyFormatLabel_3fdaf0(p, d, 0, 0);
        UiSetTextString_28f510(W, 0x20C, (s32)d, i);
        t = *(u16 *)(p + 0x10);
        UiSetWidgetSubItemValue_291250(W, 0x209, i, (long long)(t));
        hp = *(s16 *)(p + 0x1E);
        if (hp > 999) {
            hp = 999;
        }
        { s32 x = *(s16 *)(p + 0xE);
        if (x > 99) {
            x = 99;
        }
        lv = x; }
        h = (s16)hp;
        j = i * 2;
        UiSetWidgetSubItemValue_291250(W, 0x20A, j, (long long)(h));
        k = j + 1;
        UiSetWidgetSubItemValue_291250(W, 0x20A, k, (long long)((s16)lv));
        if ((s16)(u32)hp >= 100) {
            UiSetSubItemDigitCount_28f260(W, 0x20A, 3, (u32)i * 2);
        }
        if ((s16)(u32)lv >= 100) {
            UiSetSubItemDigitCount_28f260(W, 0x20A, 3, j + 1);
        }
        bits = *(u8 *)(p + 0x1C);
        if (((bits << 0x3C) >> 0x3F) != 0) {
            UiSetSpriteSizeUvSize_28f670(W, 0x1F0, 0x150, 0x2A, 4, 4, i);
            UiSetSubItemGlyphUvSize_28f100(W, 0x209, 0, 0, i);
            UiSetSubItemDigitCount_28f260(W, 0x20A, 3, ((u32)i << 1) + 1);
            UiSetSpriteSizeUvSize_28f670(W, 0x209, 0, 0, 0, 0, i);
            UiSetWidgetSubItemValue_291250(W, 0x20A, k, (long long)(h));
            UiSetSpriteSizeUvSize_28f670(W, 0x205, 0, 0, 0, 0, i);
            j = (u32)i * 2;
            UiSetSpriteSizeUvSize_28f670(W, 0x20A, 0, 0, 0, 0, j);
            UiSetSubItemGlyphUvSize_28f100(W, 0x20A, 0, 0, j);
            UiSetSpriteSizeUvSize_28f670(W, 0x206, 0x3A, 0x20, 0x56, 0x30, j);
        } else if (((bits << 0x3D) >> 0x3F) != 0) {
            UiSetSpriteSizeUvSize_28f670(W, 0x1F1, 0x150, 0x2A, 4, 4, i);
            UiSetSpriteSizeUvSize_28f670(W, 0x206, 0x3E, 0x1B, 0x56, 0x26, j + 1);
        }
    }
}
