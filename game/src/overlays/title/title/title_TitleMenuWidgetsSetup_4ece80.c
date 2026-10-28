/* rgp:protos */
#define RGP_SELF_title_TitleMenuWidgetsSetup_4ece80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004ECE80 -- BYTE-IDENTICAL (session 12).
 *
 * Build the title screen's widget set.  0.7f appears four times and is CSE'd
 * to one pool load; 0.4f once.
 *
 * ⚠ HISTORY, because this unit was parked for five sessions on a WRONG cause.
 * It read `extern f32 D_0047D248 / 0047D56C (0.7f and 0.4f)` and sat at 2 bad word(s), recorded as a
 * scheduler-internal tie-break "negative on five axes".  0x0047D1D0-0x0047D7FF
 * is not a table of globals: it is mwcc's `.lit4` FLOAT LITERAL POOL (pi,
 * pi/20, pi/40, 1/6, 0.05, -0.1, 0.4, 1e-4, with 0.4 stored twice), and retail
 * wrote the LITERAL.  Both spellings emit the same `lwc1 $fN, K($28)`; only a
 * pool entry may be hoisted past the prologue's stack stores, which is exactly
 * retail's schedule.  Every one of those five sweeps held the `extern`
 * spelling fixed.  See memory levers.d/mwcc-float-literal-pool.md.
 *
 * The `.lit4` section this now emits is resolved to the retail pool address by
 * scripts/t_lit4.py, which t_olink.py calls for every object it links.
 */

typedef struct Widget {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad8[4];
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    s16 f20;
} Widget;

typedef struct Slot {
    u8 pad0[0x20];
    Widget *f20;
} Slot;

typedef struct Title {
    u8 pad0[4];
    void *f4;
    s8 f8;
    u8 pad9[3];
    s16 fC;
    s16 fE;
    s16 f10;
    u8 pad12[2];
    f32 f14;
    f32 f18;
} Title;

extern void *D_0048415C;
extern void *D_00484174;
extern s16 D_0048419C;

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

s32 title_TitleMenuWidgetsSetup_4ece80(Title *o, void *p)
{
    Slot *s;
    Slot *z;
    Widget *w;
    s32 t;
    s32 q;
    f32 v;

    if (p == 0) {
        return 1;
    }
    o->f4 = p;
    UiSetWidgetsVisibleById_291110(o->f4, 1, 1, 1);
    s = ((Slot *)UiFindWidget_290460(o->f4, 2));
    UiSetWidgetsVisibleById_291110(o->f4, 2, 1, 1);
    t = ((s32)GetMenuResGroup_206a40());
    D_0048419C = McAnyClearedSaveFlag_372fb0();
    if (IsTgsDemoBuild_207f20() != 0) {
        s->f20 = (Widget *)ResGroupListFindValueById_42c3a0(t, 0x756C);
        UiSetWidgetsVisibleById_291110(o->f4, 3, 0, 1);
        UiSetWidgetsVisibleById_291110(o->f4, 4, 0, 1);
        UiSetWidgetsVisibleById_291110(o->f4, 5, 0, 1);
        UiSetWidgetsVisibleById_291110(o->f4, 0x66, 0, 1);
        z = ((Slot *)UiFindWidget_290460(o->f4, 6));
        z->f20->f20 = 0xD0;
    } else {
        s->f20 = (Widget *)ResGroupListFindValueById_42c3a0(t, 0x7562);
        UiSetWidgetsVisibleById_291110(o->f4, 3, 1, 1);
        UiSetWidgetsVisibleById_291110(o->f4, 4, 1, 1);
        UiSetWidgetsVisibleById_291110(o->f4, 5, 1, 1);
        if (D_0048419C != 0) {
            UiSetWidgetsVisibleById_291110(o->f4, 0x66, 1, 1);
        } else {
            UiSetWidgetsVisibleById_291110(o->f4, 0x66, 0, 1);
        }
        z = ((Slot *)UiFindWidget_290460(o->f4, 6));
        z->f20->f20 = -1;
    }
    UiSetWidgetPos_290f60(o->f4, 1, 0, 0);
    UiSetWidgetsVisibleById_291110(D_00484174, 0x46, 0, 1);
    if (title_TitleAnySaveExists_4ed380() != 0) {
        TitleCursorRowSet_206af0(1);
    } else {
        TitleCursorRowSet_206af0(0);
    }
    q = 0;
    if (IsTgsDemoBuild_207f20() == 0) {
        q = (s8)((signed char)TitleCursorRowGet_206b00());
        if (q < 0) {
            q = 0;
        }
    }
    UiSetWidgetPos_290f60(o->f4, 2, 0xB4, q * (0x18 - D_0048419C * 4) + 0x136);
    if (q != 0) {
        UiSetWidgetAlpha_2907a0(o->f4, 3, 0.7f);
        UiSetWidgetAlpha_2907a0(o->f4, 4, 1.0f);
    } else {
        UiSetWidgetAlpha_2907a0(o->f4, 3, 1.0f);
        UiSetWidgetAlpha_2907a0(o->f4, 4, 0.7f);
    }
    UiSetWidgetAlpha_2907a0(o->f4, 5, 0.7f);
    UiSetWidgetAlpha_2907a0(o->f4, 0x66, 0.7f);
    o->fC = 1;
    o->f10 = 0;
    v = 0.4f;
    o->fE = o->fC;
    o->f14 = 1.0f;
    o->f18 = v;
    o->f8 = 0;
    UiSetWidgetPos_290f60(o->f4, 3, 0xB8, 0x13B);
    if (D_0048419C != 0) {
        UiSetWidgetPos_290f60(o->f4, 4, 0xB8, 0x14F);
        UiSetWidgetPos_290f60(o->f4, 0x66, 0xB9, 0x163);
        UiSetWidgetPos_290f60(o->f4, 5, 0xB9, 0x177);
        w = ((Widget *)UiEntryListFindByTag_28ea40(D_0048415C, 0x7531));
        w->fE = 3;
    } else {
        UiSetWidgetPos_290f60(o->f4, 4, 0xB8, 0x153);
        UiSetWidgetPos_290f60(o->f4, 5, 0xB9, 0x16B);
        w = ((Widget *)UiEntryListFindByTag_28ea40(D_0048415C, 0x7531));
        w->fE = 2;
    }
    UiSetWidgetPos_290f60(o->f4, 6, 0x89, 0x18A);
    w = ((Slot *)UiFindWidget_290460(o->f4, 3))->f20;
    w->f6 = 0x10;
    w->f4 = 0x8E;
    w->fE = 0x10;
    w->fC = 0x8E;
    w = ((Slot *)UiFindWidget_290460(o->f4, 4))->f20;
    w->f6 = 0x10;
    w->f4 = 0x8E;
    w->fE = 0x10;
    w->fC = 0x8E;
    UiSetWidgetAlpha_2907a0(o->f4, 1, 0.0f);
    UiSetWidgetPos_290f60(o->f4, 1, 0, 0);
    UiSetWidgetVisible_290010(o->f4, 7, 0, -1);
    UiSetWidgetVisible_290010(o->f4, 8, 0, -1);
    UiSetWidgetVisible_290010(o->f4, 0xA, 0, -1);
    UiSetWidgetVisible_290010(o->f4, 0x47, 0, -1);
    UiSetWidgetVisible_290010(o->f4, 0x48, 0, -1);
    return 0;
}
