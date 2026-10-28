/* rgp:protos */
#define RGP_SELF_MenuModelPageSetupMaybe_35b350 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

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
extern f32 D_0047D248;
extern f32 D_0047D5E8 __attribute__((section(".sdata")));

typedef struct {
    u8 a;
    u8 b;
} B2;

typedef struct {
    u8 pad0[0x5C];
    f32 f5C;
    s32 w60;
    s32 w64;
    s32 w68[4];
    u8 pad78[0xDA - 0x78];
    s16 ids[8];
    u8 cur;
    u8 bits[8];
    B2 t0[8][2];
    B2 t1[8][2];
    u8 pad133;
    s32 w134;
    s32 w138;
    u8 pad13c[8];
    u8 sub[0x28];
    u8 b16C;
    u8 on[8];
    u8 sel;
} P;

#define W(o) (*(s32 *)(p + (o)))
#define H(o) (*(s16 *)(p + (o)))
#define B(o) (*(u8 *)(p + (o)))

/* clear helper; the `c = s` copy inside the null-check arm gives c two reaching defs (keeps it a named web) */
#define ZEROC(d, n, c, s) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) { c = s; while (n_) { *p_ = 0; n_--; p_++; } } }

void MenuModelPageSetupMaybe_35b350(P *p) {
    s32 q;
    u32 buf[2];
    s32 i;
    s32 i4;
    s32 j4;
    s32 i7;
    s32 j7;
    s32 j;
    u32 k;
    s32 gm;
    u8 *w;
    s32 v;
    s32 d;
    s32 a;
    s32 b;
    s32 e;

    p->f5C = D_0047D5E8;
    p->w60 = 0;
    p->w64 = 0;
    for (i = 0; i < 4; i++) {
        UiSetWidgetSubItemValue_291250(p->w134, 0x1E5, i, i + 1);
        UiSetWidgetSubItemValue_291250(p->w134, 0x1E6, i, 0);
        a = i * 3;
        UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E1, 0x16, 0x22, 0x16, 0x22, a);
        k = i << 1;
        k += i;
        b = k + 1;
        UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E1, 0x16, 0x22, 0x16, 0x22, b);
        k += 2;
        UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E1, 0x16, 0x22, 0x16, 0x22, k);
        UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E2, 0, 0, 0, 0, a);
        UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E2, 0, 0, 0, 0, b);
        UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E2, 0, 0, 0, 0, k);
    }
    UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E3, 0, 0, 0, 0, 0);
    UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E3, 0, 0, 0, 0, 1);
    UiSetSpriteSizeUvSize_28f670(p->w134, 0x1E3, 0, 0, 0, 0, 2);
    w = ((u8 *)UiEntryListFindByTag_28ea40(p->w138, 0x20));
    UiSetWidgetPos_290f60(p->w134, 0x1E4, *(s16 *)(w + 4), *(s16 *)(w + 6));
    *(s16 *)(w + 0x16) = 0;
    *(s16 *)(w + 0x1A) = 0;
    UiSelFrameReset_28db70(p->sub);
    UiSelFrameInit_28da30(p->sub, p->w134, 0x1DE);
    UiSelFrameSetRect_28db40(p->sub, 0x1DE, 0, 0, 0x122, 0x30, 0x1C, 0x1D);
    UiSelFrameCalcTileCounts_28d9d0(p->sub);
    UiSelFrameAnimStep_28d820(p->sub, 0x1DE);
    UiSetWidgetPos_290f60(p->w134, 0x1DE, 0x10, 0x11);
    UiSetWidgetVisible_290010(p->w134, 0x1D2, 0, -1);
    UiSetWidgetAlpha_2907a0(p->w134, 0x1D2, 0.0f);
    MenuModelPageCharaInfoLayoutMaybe_359700((u8 *)p);
    p->b16C = 0;
    p->sel = 0;
    for (i = 0; i < 8; i++) {
        p->on[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        p->w68[i] = 0;
    }
    j = ((s32)GetGameData_1fede0());
    gm = j;
    p->cur = 0;
    for (i4 = 0; i4 < 8; i4++) {
        p->bits[i4] = 0;
        for (j4 = 0; j4 < 2; j4++) {
            p->t0[i4][j4].a = 0;
            p->t0[i4][j4].b = 0;
            p->t1[i4][j4].a = 0;
            p->t1[i4][j4].b = 0;
        }
    }
    if (*(s16 *)(*(s32 *)(gm + 0xC) + 0x26) == 1) {
        v = (s16)((short)PartyMenuCursorGet_3c0760(*(s32 *)(gm + 0x18), 0xF));
        p->cur = v & 7;
        for (i = 0; i < 8; i++) {
            p->bits[i] = (v >> (i + 3)) & 1;
        }
        for (i = 0; i < 8; i++) {
            d = p->ids[i] - 0x2AF9;
            if (d < 0) {
                p->on[i] = 0;
            } else {
                if (d == p->cur) {
                    p->sel = i;
                }
                p->on[i] = p->bits[d];
            }
        }
        for (i7 = 0; i7 < 8; i7++) {
            for (j7 = 0; j7 < 2; j7++) {
                p->t0[i7][j7].a = 0;
                p->t0[i7][j7].b = 0;
                p->t1[i7][j7].a = 0;
                p->t1[i7][j7].b = 0;
            }
        }
        for (q = 0; q < 8; q++) {
            d = p->ids[q] - 0x2AF9;
            if (d < 0) {
                continue;
            }
            e = d;
            v = (s16)((short)PartyMenuCursorGet_3c0760(*(s32 *)(gm + 0x18), e + 0x1C));
            ZEROC(buf, 8, e, d);
            buf[0] = v & 0xFF;
            buf[1] = (v >> 8) & 0xFF;
            for (j = 0; j < 2; j++) {
                p->t0[e][j].a = 0;
                p->t0[e][j].b = buf[j];
                p->t1[e][j].a = 0;
                p->t1[e][j].b = 0;
            }
        }
    }
    MenuModelPageCharaLabelLayoutMaybe_359120((u8 *)p);
    MenuModelPageTabSpritesUpdate_3593e0((u8 *)p);
    w = ((u8 *)UiEntryListFindByTag_28ea40(p->w138, 0x28));
    *(s16 *)(w + 0x16) = p->sel;
    *(s16 *)(w + 0x1A) = 0;
    UiSetWidgetPos_290f60(p->w134, 0x258, 0, 0x10B);
    UiSetWidgetPos_290f60(p->w134, 0x262, 0, 0x12E);
    UiSetWidgetColor_2905b0(p->w134, 0x258, D_0047D248, D_0047D248, D_0047D248, 1.0f);
    { f32 o = 1.0f; UiSetWidgetColor_2905b0(p->w134, 0x262, D_0047D248, D_0047D248, D_0047D248, o); }
}
