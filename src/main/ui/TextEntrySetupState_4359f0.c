#include "types.h"

typedef struct Pos {
    u8 pad0[0x4];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    u8 pad10[0x4];
    s16 x14;
    s16 x16;
} Pos;

typedef struct Spr {
    u8 pad0[0x20];
    s32 x20;
} Spr;

typedef struct Clr {
    u8 pad0[0xC];
    s32 xC;
} Clr;

typedef struct W {
    s32 x0;
    u8 pad4[0x4];
    s16 x8;
} W;

typedef struct Sub {
    u8 pad0[0x1188];
    W *x1188;
} Sub;

typedef struct Game {
    u8 pad0[0x24];
    Sub *x24;
} Game;

typedef struct Menu {
    s32 x0;
    s32 x4;
    u8 pad8[0x4];
    s32 xC;
    s32 x10;
    s32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    s16 x28;
    s16 x2A;
    s16 x2C;
    s16 x2E;
    u8 x30[0xB0];
    s16 xE0;
    s16 xE2;
    s16 xE4;
    u8 padE6[0x160];
    u8 x246;
} Menu;

typedef struct XY {
    s16 x;
    s16 y;
} XY;

typedef struct XYZ {
    s16 x;
    s16 y;
    s16 z;
} XYZ;

typedef struct T5a { XY v[5]; } T5a;
typedef struct T5b { XYZ v[5]; } T5b;
typedef struct T5c { s16 v[5]; } T5c;

extern Game *GetGameData_1fede0(void);
extern s32 GetDrawCtx_15de80(void);
extern s32 DrawEnvGetVsyncInterval_144130(s32);
extern Pos *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern Spr *UiFindWidget_290460(s32, s32);
extern void UiLayoutFrameRectsMaybe_28bbb0(s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, char *, s32);
extern char *MsgTableLookup_28aa30(s32, s32);
extern Clr *UiGetWidgetText_28f620(s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetTextPos_28f5d0(s32, s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void *memset(void *, s32, u32);
extern void TextEntryBuildTemplateText_4356d0(Menu *, s32, s32);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern void UiSetTextY_28f550(s32, s32, s32, s32);
extern void TextEntryHideMaskedCells_435920(Menu *);
extern void TextEntryMarkStarCells_4357b0(Menu *, s32, s32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void TextEntrySetState_434410(Menu *, u16, s32);
extern const f32 D_0047D34C __attribute__((section(".sdata")));
extern const f32 D_0047D3C8 __attribute__((section(".sdata")));
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern const f32 D_0047D240 __attribute__((section(".sdata")));
extern const f32 D_0047D408 __attribute__((section(".sdata")));
extern const f32 D_0047D3D0 __attribute__((section(".sdata")));
extern const f32 D_0047D40C __attribute__((section(".sdata")));
extern s16 D_004552F0[];
extern s16 D_00455310[];
extern s16 D_00480320[] __attribute__((section(".sdata")));
extern s16 D_00480330[] __attribute__((section(".sdata")));
extern s16 D_00480340[] __attribute__((section(".sdata")));
extern s16 D_00484128;

static inline void SetCol(Menu *m, f32 r, f32 g, f32 b, f32 a) {
    m->x18 = r;
    m->x1C = g;
    m->x20 = b;
    m->x24 = a;
}

s32 TextEntrySetupState_4359f0(Menu *m, s32 init) {
    s32 vBC;
    s32 vB8;
    s32 vB4;
    s32 vB0;
    T5c tA0;
    T5c t90;
    T5c t80;
    T5a t60;
    T5b t40;
    Game *g;
    s32 k;
    Pos *p;
    Spr *r;
    Clr *c;
    s32 x;
    s32 y;
    s32 s;
    W *w;
    s32 v;
    s32 id;
    f32 fr;
    f32 fg;
    f32 fb;
    f32 fa;
    f32 fr2;
    f32 fg2;
    f32 fb2;

    g = GetGameData_1fede0();
    if (init != 0) {
        k = DrawEnvGetVsyncInterval_144130(GetDrawCtx_15de80());
        fr = D_0047D34C;
        fg = D_0047D3C8;
        fb = D_0047D3B8;
        fa = 0.25f;
        SetCol(m, fr, fg, fb, fa);
        if (k == 1) {
            SetCol(m, fr, fg, fb, fa);
        } else if (k == 2) {
            SetCol(m, D_0047D240, D_0047D408, D_0047D3D0, 0.5f);
        }
        p = UiEntryListFindByTag_28ea40(m->x4, 0x6D61);
        if (p != 0) {
            p->x16 = 0;
            p->x14 = 0;
        }
        p = UiEntryListFindByTag_28ea40(m->x4, 0x6D62);
        if (p != 0) {
            p->x16 = 0;
            p->x14 = 0;
        }
        UiSetWidgetVisible_290010(m->x0, 1, 1, -1);
        UiSetWidgetAlpha_2907a0(m->x0, 1, 0.0f);
        UiFadeWidgetAlpha_290690(m->x0, 1, 1.0f, m->x18, -1.0f);
        r = UiFindWidget_290460(m->x0, 2);
        t60 = *(T5a *)D_004552F0;
        UiLayoutFrameRectsMaybe_28bbb0(r->x20, t60.v[m->xE0].x, t60.v[m->xE0].y);
        UiSetTextString_28f510(m->x0, 2, 0, 0);
        if (m->xE0 == 4) {
            UiSetTextString_28f510(m->x0, 2, MsgTableLookup_28aa30(m->xC, 0xF0), 0);
            c = UiGetWidgetText_28f620(m->x0, 2, 0);
            if (c != 0) {
                c->xC = 0xFF181840;
            }
        }
        t40 = *(T5b *)D_00455310;
        UiSetWidgetPos_290f60(m->x0, 2, t40.v[m->xE0].x, t40.v[m->xE0].y);
        UiSetWidgetPos_290f60(m->x0, 0xE, t40.v[m->xE0].z, 0x1E);
        UiSetWidgetColor_2905b0(m->x0, 0xE, 0.5f, 0.5f, 0.5f, -1.0f);
        UiLayoutFrameRectsMaybe_28bbb0(UiFindWidget_290460(m->x0, 0x14)->x20, 0x70, 0x24);
        UiSetWidgetPos_290f60(m->x0, 0x14, 0x17F, 0x10F);
        UiSetTextString_28f510(m->x0, 0x14, MsgTableLookup_28aa30(m->xC, 0xE), 0);
        UiSetTextPos_28f5d0(m->x0, 0x14, 0xE, 0xA, 0);
        UiLayoutFrameRectsMaybe_28bbb0(UiFindWidget_290460(m->x0, 4)->x20, 0x1E0, 0x58);
        if (m->xE0 == 4) {
            UiSetWidgetsVisibleById_291110(m->x0, 3, 0, 1);
            UiSetWidgetsVisibleById_291110(m->x0, 0x14, 0, 1);
        } else {
            UiSetWidgetsVisibleById_291110(m->x0, 3, 1, 1);
            UiSetWidgetsVisibleById_291110(m->x0, 0x14, 1, 1);
        }
        UiSetWidgetPos_290f60(m->x0, 3, 0, 0x14);
        UiSetWidgetPos_290f60(m->x0, 4, 0xF, 0x12C);
        UiGetWidgetPos_2910a0(m->x0, 4, &vBC, &vB8);
        UiSetWidgetPos_290f60(m->x0, 0xC, vBC, vB8);
        UiSetWidgetsVisibleById_291110(m->x0, 0xC, 1, 1);
        UiSetWidgetAlpha_2907a0(m->x0, 0xC, 0.0f);
        UiFadeWidgetAlpha_290690(m->x0, 0xC, 1.0f, m->x18, -1.0f);
        p = UiEntryListFindByTag_28ea40(m->x4, 0x6D61);
        UiGetWidgetPos_2910a0(m->x0, 4, &vBC, &vB8);
        x = vBC + (p->x4 + p->x14 * p->x8);
        y = vB8 + (p->x6 + p->x16 * p->xA);
        p->x16 = 0;
        p->x14 = 0;
        UiSetWidgetPos_290f60(m->x0, 0xC, x, y);
        if (m->xE0 == 4) {
            UiSetWidgetsVisibleById_291110(m->x0, 4, 0, 1);
            UiSetWidgetsVisibleById_291110(m->x0, 6, 0, 1);
            UiSetWidgetsVisibleById_291110(m->x0, 0xC, 0, 1);
        }
        m->x10 = 0;
        m->x14 = 0;
        UiSetWidgetPos_290f60(m->x0, 5, 0x19, 9);
        UiSetWidgetPos_290f60(m->x0, 6, 0, 0x192);
        UiSetWidgetPos_290f60(m->x0, 8, 0x19A, 9);
        UiSetWidgetPos_290f60(m->x0, 9, 0x19A, 0x22);
        UiSetWidgetPos_290f60(m->x0, 0xA, 0x19A, 0x3B);
        m->x28 = 0;
        m->x2A = 0;
        m->x2C = 0;
        m->x2E = 0;
        m->xE2 = 0;
        m->xE4 = 1;
        m->x246 = 1;
        memset(m->x30, 0, 0xAF);
        UiSetTextString_28f510(m->x0, 0xB, (char *)m->x30, 0);
        TextEntryBuildTemplateText_4356d0(m, 1, 0);
        tA0 = *(T5c *)D_00480320;
        UiSetWidgetPos_290f60(m->x0, 0xB, tA0.v[m->xE0], 0xB);
        k = m->xE0;
        if (k == 1 || k == 3) {
            s = 0x408;
        } else if (k == 0) {
            s = m->xE2 + 0x1E;
        } else {
            s = m->xE2 + 0x406;
        }
        UiSetTextString_28f510(m->x0, 5, MsgTableLookup_28aa30(m->xC, s), 0);
        UiSetTextString_28f510(m->x0, 8, MsgTableLookup_28aa30(m->xC, m->xE2 + 0xA), 0);
        UiSetTextString_28f510(m->x0, 9, MsgTableLookup_28aa30(m->xC, 0xC), 0);
        UiSetTextString_28f510(m->x0, 0xA, MsgTableLookup_28aa30(m->xC, 0xD), 0);
        if (m->xE0 == 1 || m->xE0 == 3) {
            UiSetTextString_28f510(m->x0, 8, MsgTableLookup_28aa30(m->xC, 0xC), 0);
            UiSetTextString_28f510(m->x0, 9, MsgTableLookup_28aa30(m->xC, 0xD), 0);
            UiSetTextString_28f510(m->x0, 0xA, 0, 0);
        }
        if (m->xE0 == 1 || m->xE0 == 3) {
            UiSetTextString_28f510(m->x0, 6, 0, 0);
        } else {
            UiSetTextString_28f510(m->x0, 6, MsgTableLookup_28aa30(m->xC, m->xE2), 0);
        }
        UiSetTextString_28f510(m->x0, 6, MsgTableLookup_28aa30(m->xC, 2), 1);
        UiSetTextString_28f510(m->x0, 6, MsgTableLookup_28aa30(m->xC, 3), 2);
        t90 = *(T5c *)D_00480330;
        k = m->xE0;
        w = g->x24->x1188;
        s = t90.v[k];
        if (w->x0 != 0) {
            if (k == 0 || k == 4) {
                v = w->x8;
                if (v == 0x1F6) {
                    s = 0x14;
                } else if (v == 0x1F7) {
                    s = 0x15;
                } else if (v == 0x193) {
                    s = 0x15;
                }
            }
        }
        UiSetTextString_28f510(m->x0, 3, MsgTableLookup_28aa30(m->xC, s), 0);
        UiSetTextCenteredX_28f300(m->x0, 3, 0x100, 0);
        UiSetTextY_28f550(m->x0, 3, 0xA, 0);
        if (m->x4 != 0) {
            t80 = *(T5c *)D_00480340;
            p = UiEntryListFindByTag_28ea40(m->x4, 0x6D62);
            p->x4 = t80.v[m->xE0];
            p->x6 = 0xB;
            p->xC = 0x1C;
            p->xE = 5;
            k = m->xE0;
            if (k == 1) {
                goto z;
            }
            if (k == 2) {
                goto z;
            }
            if (k == 3) {
            z:
                p->xE = 0;
            }
            p->x8 = 0xE;
            p->xA = 0x1C;
            UiGetWidgetPos_2910a0(m->x0, 2, &vB4, &vB0);
            UiSetWidgetPos_290f60(m->x0, 7, vB4 + (p->x4 + p->x14 * p->x8), vB0 + (p->x6 + p->x16 * p->xA));
        }
        TextEntryHideMaskedCells_435920(m);
        TextEntryMarkStarCells_4357b0(m, -1, -1);
        D_00484128 = 0;
    }
    if (!(UiGetWidgetAlpha_290770(m->x0, 1) < 1.0f)) {
        if (m->xE0 != 4) {
            UiSetWidgetsVisibleById_291110(m->x0, 7, 1, 1);
            UiSetWidgetAlpha_2907a0(m->x0, 7, 0.0f);
            UiFadeWidgetAlpha_290690(m->x0, 7, D_0047D40C, m->x18, -1.0f);
            UiSetWidgetsVisibleById_291110(m->x0, 0xD, 1, 1);
            UiSetWidgetAlpha_2907a0(m->x0, 0xD, 0.0f);
        }
        k = m->xE0;
        id = 0x6D62;
        if (k != 0 && k != 4) {
            id = 0x6D6A;
        }
        TextEntrySetState_434410(m, id, 0);
    }
    return 0;
}
