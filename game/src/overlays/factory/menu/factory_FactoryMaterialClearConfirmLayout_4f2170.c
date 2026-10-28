/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialClearConfirmLayout_4f2170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F2170 -- centre the factory confirmation dialog.
 *
 * 276 instructions, 38 calls, 6 conditional branches.  Same family as
 * 0x004EA870 and 0x004F7ED0: measure the text, halve it, centre it, then place
 * the three-slice frame and the button row.
 *
 * ★ `sra` under `bgez` with a +1 bias is a signed `/ 2`, five times.
 * ★ The screen size is read ONCE (`func_15DE80`) and fed to both
 * func_1451E0 (width) and func_1451D0 (height).
 * ★ `func_28FD10(..., row->f0 + 2 + row->f18, ...)` reads back the field the
 * previous statement stored; retail FORWARDS it with `dsll32`/`dsra32` rather
 * than issuing an `lh`, which is the recorded store-then-read shape.
 */

typedef struct Box {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
} Box;

typedef struct Item {
    u8  pad0[4];
    Box b;
} Item;

typedef struct Layout {
    void *f0;
    s32   f4;
    u8    pad8[8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    u8    pad20[0x14];
} Layout;

typedef struct Row {
    s16 f0;
    u8  pad2[0x16];
    s16 f18;
} Row;

typedef struct Ctx {
    u8    pad0[0x1E];
    u8    f1E;
    u8    pad20[0x20];
    void *f40;
    void *f44;
} Ctx;

extern void *D_004807EC;
extern void *D_00484A70;

extern void  memset(void *p, s32 v, s32 n);
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
/*rgp*/

void factory_FactoryMaterialClearConfirmLayout_4f2170(Ctx *o)
{
    Layout lay __attribute__((aligned(16)));
    Item *g;
    Box *b;
    Row *row;
    s32 s;
    s32 cw;
    s32 ch;
    s32 x;
    s32 y;
    s32 xl;
    s32 r;
    s32 t;
    s32 ty;

    UiSetTextString_28f510(o->f40, 0x6A, MsgTableLookup_28aa30(D_00484A70, 0x13), 0);
    UiSetTextString_28f510(o->f40, 0x6A, MsgTableLookup_28aa30(D_00484A70, 0xC), 1);
    UiSetTextString_28f510(o->f40, 0x6A, MsgTableLookup_28aa30(D_00484A70, 0xD), 2);

    memset(&lay, 0, 0x34);
    lay.f0 = ((Row *)UiGetWidgetSprite_28fe10(o->f40, 0x6A, 0));
    lay.f4 = ((s32)UiGetWidgetText_28f620(o->f40, 0x6A, 0));
    lay.f10 = 0x1C;
    lay.f14 = 0x30;
    lay.f18 = 0xF;
    lay.f1C = 8;
    cw = lay.f10 + UiGetWidgetTextWidth_28f400(o->f40, 0x6A, 0);
    ch = lay.f14 + UiGetWidgetTextHeight_28f3d0(o->f40, 0x6A, 0);
    if (cw < 0xFA) {
        lay.f10 = lay.f10 + (0xFA - cw);
        cw = 0xFA;
    }
    s = GetDrawCtx_15de80();
    x = DrawEnvGetWidth_1451e0(s) / 2 - cw / 2;
    y = DrawEnvGetHeight_1451d0(s) / 2 - ch / 2;
    xl = x + 0x10;
    r = xl + (cw - 0x20);

    g = ((Item *)UiEntryListFindByTag_28ea40(o->f44, 0x893A));
    g->b.f10 = 1;
    g->b.f12 = 0;
    ty = y + 0x24;
    g->b.f0 = x + 0x1B;
    b = &g->b;
    g->b.f2 = ty;
    t = (r - 0x57) - (x + 0x39);
    g->b.f4 = t;
    g->b.f6 = 0;
    g->b.f8 = 1;
    g->b.fA = 0;
    UiSetSpritePos_28fd10(o->f40, 0x75, x + 0x39, ty, 0);
    UiSetSpritePos_28fd10(o->f40, 0x75, x + 0x3D, y + 0x24, 1);
    UiSetSpritePos_28fd10(o->f40, 0x75, x + 0x6D, y + 0x24, 2);
    row = ((Row *)UiGetWidgetSprite_28fe10(o->f40, 0x75, 0));
    row->f18 = t;
    row = ((Row *)UiGetWidgetSprite_28fe10(o->f40, 0x75, 1));
    row->f18 = t;
    row = ((Row *)UiGetWidgetSprite_28fe10(o->f40, 0x75, 2));
    row->f18 = t;
    UiSetSpritePos_28fd10(o->f40, 0x75, row->f0 + 2 + row->f18, y + 0x24, 3);
    UiWindowFitToText_28d0c0(&lay, 0, 0, 0);

    UiSetTextY_28f550(o->f40, 0x6A, y + 8, 0);
    UiSetTextCenteredX_28f300(o->f40, 0x6A, xl + (cw - 0x20) / 2, 0);
    UiSetTextY_28f550(o->f40, 0x6A, y + 0x28, 1);
    UiSetTextCenteredX_28f300(o->f40, 0x6A, x + 0x53, 1);
    UiSetTextY_28f550(o->f40, 0x6A, y + 0x28, 2);
    UiSetTextCenteredX_28f300(o->f40, 0x6A, r - 0x3D, 2);
    UiSetSpritePosSize_28fd70(o->f40, 0x6E, x + 0xA, y + 0x1B, 0xA, 6, 0);
    UiSetSpritePosSize_28fd70(o->f40, 0x6E, x + 0x14, y + 0x1B, cw - 0x2B, 6, 1);
    UiSetSpritePosSize_28fd70(o->f40, 0x6E, x + 9 + (cw - 0x20), y + 0x1B, 0xA, 6, 2);

    UiSetWidgetVisible_290010(o->f40, 0x6A, 0, -1);
    UiSetWidgetVisible_290010(D_004807EC, 0x97, 0, -1);
    UiSetWidgetAlpha_2907a0(o->f40, 0x6A, 0.0f);
    UiSetWidgetAlpha_2907a0(D_004807EC, 0x97, 0.0f);
    UiSetWidgetPos_290f60(o->f40, 0x6A, -0x2F, -0xAF);
    UiSetWidgetPos_290f60(D_004807EC, 0x97, b->f0 + b->f10 * b->f4, b->f2);
    o->f1E = 1;
}
