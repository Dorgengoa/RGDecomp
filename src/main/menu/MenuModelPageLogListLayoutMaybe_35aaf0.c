#include "types.h"

typedef struct Item {
    u8 pad[0x2C];
    s16 id;
} Item;

typedef struct Slot {
    Item *p;
    u8 f0 : 1;
    u8 on : 1;
    u8 fr : 6;
    u8 pad[3];
} Slot;

typedef struct Ent {
    u16 id : 10;
    u16 b10 : 1;
    u16 b11 : 1;
    u16 b12 : 4;
    u8 pad2[2];
    Slot s[3];
} Ent;

typedef struct Hdr {
    u8 pad[0x14];
    s16 n;
    u8 pad16[2];
    Ent *ent;
} Hdr;

typedef struct Sub8 {
    u8 pad[0x90];
    Hdr *hdr;
} Sub8;

typedef struct SubC {
    u8 pad[0x26];
    s16 mode;
} SubC;

typedef struct W {
    u8 pad[8];
    Sub8 *p8;
    SubC *pC;
} W;

typedef struct L {
    u8 pad[0xE];
    s16 fE;
    u8 pad10[2];
    s16 f12;
    u8 pad14[2];
    s16 f16;
    u8 pad18[2];
    s16 f1A;
} L;

typedef struct Obj {
    u8 pad0[0x60];
    s32 f60;
    f32 f64;
    Ent *f68[4];
    u8 pad78[0xDA - 0x78];
    s16 f0DA[4];
    u8 padE2[0xF4 - 0xE2];
    u8 tA[8][2][2];
    u8 tB[8][2][2];
    s32 p134;
    s32 p138;
    u8 pad13C[0x16D - 0x13C];
    u8 b16D[8];
    u8 b175;
} Obj;

W *GetGameData_1fede0(void);
void UiSetItemIconUv_288e50(s32, s32, s32, s32);
f32 UiPageScrollBarLayout_289710(Obj *, s32, s32, s32, s32, s32);
L *UiEntryListFindByTag_28ea40(s32, s32);
void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
void WeaponCombineLogCollect_3e9270(W *, s32, s32);
extern f32 D_0047D5B8;

#pragma opt_lifetimes off
void MenuModelPageLogListLayoutMaybe_35aaf0(Obj *o) {
    s32 k0;
    W *w;
    s32 j;
    s32 k;
    s32 base;
    s32 flag;
    s32 n;
    Ent *e;
    s32 id;
    s32 a;
    s32 i;
    s32 j2;
    s32 q;
    s16 fl[3];
    s32 ids[3];
    s16 cnt;
    L *t;
    s32 lo;
    s32 v8;
    s32 d7;
    s32 v5;
    s32 v3;
    s32 c;
    s32 b;
    s32 hi;
    s32 idx;
    s32 sel;
    s32 x;



    w = GetGameData_1fede0();
    UiSetWidgetColor_2905b0(o->p134, 0x1E2, D_0047D5B8, D_0047D5B8, D_0047D5B8, 1.0f);
    UiSetWidgetPos_290f60(o->p134, 0x1DE, 0x10, 0x11);
    o->f60 = 0;
    for (b = 0; b < 4; b++) {
        o->f68[b] = 0;
        UiSetWidgetSubItemValue_291250(o->p134, 0x1E5, b, b + 1);
        UiSetWidgetSubItemValue_291250(o->p134, 0x1E6, b, 0);
        k0 = b * 3;
        for (c = 0; c < 3; c++) {
            q = c + k0;
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E1, 0, 0, 0, 0, q);
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1DC, 0, 0, 0, 0, b);
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1D6, 0, 0, 0, 0, b);
            UiSetSpriteFlags_290bd0(o->p134, 0x1E2, 0x200, 0, c + (s32)k0, 0);
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E2, 0, 0, 0, 0, q);
            k0 = b * 3;
        }
    }
    UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E3, 0, 0, 0, 0, 0);
    UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E3, 0, 0, 0, 0, 1);
    UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E3, 0, 0, 0, 0, 2);
    UiSetWidgetsVisibleById_291110(o->p134, 0x1D6, 1, 1);
    UiSetWidgetAlpha_2907a0(o->p134, 0x1D6, D_0047D5B8);
    UiSetWidgetPos_290f60(o->p134, 0x1D6, 0x20, 0x23);
    k = o->b175;
    flag = 0;
    if (o->b16D[k] == 1) flag = 1;
    WeaponCombineLogCollect_3e9270(w, o->f0DA[k], flag);
    n = w->p8->hdr->n;
    e = w->p8->hdr->ent;
    for (i = 0; i < n; e++, i++) {
        if (e == 0) continue;
        if (i >= 4) continue;
        id = e->id;
        a = -1;
        b = -1;
        c = -1;
        if (e->s[0].p) {
            a = e->s[0].p->id;
            UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(o->p134, 0x1E2, i * 3), a, 0x28, 0x2D);
        }
        if (e->s[1].p) {
            b = e->s[1].p->id;
            UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(o->p134, 0x1E2, i * 3 + 1), b, 0x28, 0x2D);
        }
        if (e->s[2].p) {
            c = e->s[2].p->id;
            UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(o->p134, 0x1E2, i * 3 + 2), c, 0x28, 0x2D);
        }
        ids[0] = a;
        ids[1] = b;
        o->f68[i] = e;
        ids[2] = c;
        cnt = 0;
        base = i * 3;
        fl[0] = e->s[0].on;
        fl[1] = e->s[1].on;
        fl[2] = e->s[2].on;
        for (b = 0; b < 3; b++) {
            if (fl[b] == 0) {
                if (ids[b] < 0) {
                    k = b + base;
                    UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E2, 0, 0, 0, 0, k);
                    UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E1, 0x16, 0x22, 0x16, 0x22, k);
                } else {
                    UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E1, 0, 0, 0, 0, b + base);
                }
            } else {
                UiSetSpriteFlags_290bd0(o->p134, 0x1E2, 0xA, 0, b + (s32)base, 0);
                UiSetSpriteSizeUvSize_28f670(o->p134, 0x1E1, 0, 0, 0, 0, b + base);
                cnt++;
            }
        }
        if (cnt == 3 && id == 0 && e->s[2].p != 0) {
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1D6, 0x129, 0x34, 4, 4, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1D6, 0, 0, 0, 0, i);
        }
        if (e->b11) {
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1DC, 0x2A, 0x14, 0x2A, 0x14, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(o->p134, 0x1DC, 0, 0, 0, 0, i);
        }
        UiSetWidgetSubItemValue_291250(o->p134, 0x1E6, i, id);
    }
    o->f64 = UiPageScrollBarLayout_289710(o, 0x1D9, 0xE3, 4, n, 0);
    UiSetWidgetPos_290f60(o->p134, 0x1D9, 0x14D, 0x1E);
    t = UiEntryListFindByTag_28ea40(o->p138, 0x20);
    t->f12 = n - 1;
    if (w->pC->mode != 1) return;
    k = o->b175;
    idx = ((volatile s16 *)o->f0DA)[k];
    sel = o->b16D[k];
    x = idx - 0x2AF9;
    v5 = o->tA[x][sel][0];
    v3 = o->tB[x][sel][0];
    lo = t->fE;
    hi = t->f12;
    d7 = hi - lo;
    v8 = lo;
    if (lo < 0) v8 = 0;
    if (d7 < 0) d7 = 0;
    if (v8 < v5) {
        v3 = v5 - lo;
        if (v3 > 0) v5 -= v3;
    }
    if (v5 < 0) {
        v5 = 0;
    } else if (v8 < v5) {
        v5 = v8;
    }
    if (v3 < 0) {
        v3 = 0;
    } else if (d7 < v3) {
        v3 = d7;
    }
    t->f16 = v5;
    t->f1A = v3;
}
