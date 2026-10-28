/* rgp:protos */
#define RGP_SELF_MenuModelPageLogRowsRefreshMaybe_35a1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Thing {
    u8 pad0[0x2C];
    s16 x2C;
} Thing;

typedef struct Sub {
    Thing *t;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 6;
    u8 pad[3];
} Sub;

typedef struct Slot {
    __extension__ unsigned short id : 10;
    unsigned short f10 : 1;
    unsigned short f11 : 1;
    unsigned short f12 : 4;
    u8 pad2[2];
    Sub sub[3];
} __attribute__((aligned(2))) Slot;

typedef struct Tbl {
    u8 pad0[0x14];
    s16 n;
    u8 pad16[2];
    Slot *base;
} Tbl;

typedef struct Inner {
    u8 pad0[0x90];
    Tbl *tbl;
} Inner;

typedef struct Ent {
    u8 pad0[8];
    Inner *in;
} Ent;

typedef struct Rect {
    u8 pad0[0xE];
    s16 xE;
    u8 pad10[2];
    s16 x12;
    u8 pad14[6];
    s16 x1A;
} Rect;

typedef struct Obj {
    u8 pad0[0x68];
    Slot *slot[4];
    u8 pad78[0xDA - 0x78];
    s16 xDA[0x2D];
    s32 x134;
    s32 x138;
    u8 pad13C[0x16D - 0x13C];
    u8 x16D[8];
    u8 x175;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D440;

#pragma opt_lifetimes off
void MenuModelPageLogRowsRefreshMaybe_35a1a0(Obj *a) {
    Ent *e;
    Rect *r;
    s32 top;
    s32 d;
    s32 i;
    s32 k;
    s32 cnt;
    s32 j;
    Tbl *tb;
    u8 idx;
    s32 flag;
    Slot *p;
    s32 fp;
    s32 id0;
    s32 id1;
    s32 id2;
    s32 base;
    s16 n;
    s32 v;
    s32 n2;
    Slot *sb;
    s16 fl[3];
    s32 id[3];
    s32 i0;

    e = ((Ent *)GetGameData_1fede0());
    r = ((Rect *)UiEntryListFindByTag_28ea40(a->x138, 0x20));
    top = r->x1A;
    if (top < 0) {
        top = 0;
    } else {
        d = r->xE;
        d = r->x12 - d;
        if (d < top) {
            top = d;
            if (top < 0) top = 0;
        }
    }
    UiSetWidgetColor_2905b0(a->x134, 0x1E2, D_0047D440, D_0047D440, D_0047D440, 1.0f);
    for (i0 = 0; i0 < 4; i0++) {
        k = i0 * 3;
        UiSetSpriteFlags_290bd0(a->x134, 0x1E2, (long long)(0x200), 0, k, 0);
        UiSetSpriteFlags_290bd0(a->x134, 0x1E2, (long long)(0x200), 0, k + 1, 0);
        UiSetSpriteFlags_290bd0(a->x134, 0x1E2, (long long)(0x200), 0, k + 2, 0);
    }
    for (i0 = 0; i0 < 4; i0++) {
        a->slot[i0] = 0;
        UiSetWidgetSubItemValue_291250(a->x134, 0x1E6, i0, 0);
    }
    idx = a->x175;
    v = a->xDA[idx];
    flag = 0;
    if (a->x16D[idx] == 1) flag = 1;
    WeaponCombineLogCollect_3e9270(e, v, flag, 0);
    cnt = 0;
    tb = e->in->tbl;
    n2 = tb->n;
    sb = tb->base;
    for (j = top; j < n2; j++) {
        a->slot[cnt++] = &sb[j];
        if (cnt >= 4) break;
    }
    for (i = 0; i < 4; i++) {
        p = a->slot[i];
        if (p == 0) continue;
        fp = p->id;
        id0 = -1;
        id1 = id0;
        id2 = id0;
        if (p->sub[0].t != 0) {
            id0 = p->sub[0].t->x2C;
            UiSetItemIconUv_288e50(((s32)UiGetWidgetSprite_28fe10(a->x134, 0x1E2, i * 3)), id0, 0x28, 0x2D);
        }
        if (p->sub[1].t != 0) {
            id1 = p->sub[1].t->x2C;
            UiSetItemIconUv_288e50(((s32)UiGetWidgetSprite_28fe10(a->x134, 0x1E2, i * 3 + 1)), id1, 0x28, 0x2D);
        }
        if (p->sub[2].t != 0) {
            id2 = p->sub[2].t->x2C;
            UiSetItemIconUv_288e50(((s32)UiGetWidgetSprite_28fe10(a->x134, 0x1E2, i * 3 + 2)), id2, 0x28, 0x2D);
        }
        n = 0;
        d = 0;
        id[0] = id0;
        base = i * 3;
        id[1] = id1;
        id[2] = id2;
        fl[0] = p->sub[0].b1;
        fl[1] = p->sub[1].b1;
        fl[2] = p->sub[2].b1;
        for (; d < 3; d++) {
            if (fl[d] == 0) {
                if (id[d] < 0) {
                    k = d + base;
                    UiSetSpriteSizeUvSize_28f670(a->x134, 0x1E2, 0, 0, 0, 0, k);
                    UiSetSpriteSizeUvSize_28f670(a->x134, 0x1E1, 0x16, 0x22, 0x16, 0x22, k);
                } else {
                    UiSetSpriteSizeUvSize_28f670(a->x134, 0x1E1, 0, 0, 0, 0, d + base);
                }
            } else {
                UiSetSpriteFlags_290bd0(a->x134, 0x1E2, (long long)(0xA), 0, (u32)d + base, 0);
                UiSetSpriteSizeUvSize_28f670(a->x134, 0x1E1, 0, 0, 0, 0, d + base);
                n++;
            }
        }
        if (n == 3 && fp == 0 && p->sub[2].t != 0) {
            UiSetSpriteSizeUvSize_28f670(a->x134, 0x1D6, 0x129, 0x34, 4, 4, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(a->x134, 0x1D6, 0, 0, 0, 0, i);
        }
        if (p->f11) {
            UiSetSpriteSizeUvSize_28f670(a->x134, 0x1DC, 0x2A, 0x14, 0x2A, 0x14, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(a->x134, 0x1DC, 0, 0, 0, 0, i);
        }
        UiSetWidgetSubItemValue_291250(a->x134, 0x1E6, i, fp);
        UiSetWidgetSubItemValue_291250(a->x134, 0x1E5, i, top + 1 + i);
    }
}
