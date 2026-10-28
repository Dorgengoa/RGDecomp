/* rgp:protos */
#define RGP_SELF_endBox 1
#define RGP_SELF_factory_FactoryProduceShowMessage_4f62d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F62D0 -- lay out the factory screen's message box
 * for one prompt kind.
 *
 * 520 instructions, TWO jump tables (factory_jtbl_0050CC80 for `kind` 0..5 and
 * factory_jtbl_0050CC40 for the sub-kind 8..21).  Both are the overlay's own data, and
 * scripts/f_jtbl.py is what lets a compiled `switch` use them instead of
 * emitting a second copy into the object's .rodata.
 *
 * ★ The four-store + func_28D0C0 tail is an INLINED HELPER, not a shared
 * label: retail emits it five times -- once at the end of each of cases 1, 2,
 * 3 and 5, and once after case 4's inner switch, which every inner arm
 * `break`s out to.  A shared `goto` would have emitted it once.
 *
 * ★ Case 0 is the only arm that computes its own four values, so it does not
 * use the helper; it calls func_28D0C0 itself.
 *
 * ★ `sra` with a +1 bias under `bgez` is a signed `/ 2`; m2c writes the bias
 * out longhand and the plain division compiles to the same code.
 *
 * ★ factory_D_0050CC38 and factory_D_0050FED0 are OVERLAY data at 0x50xxxx, far outside the
 * gp window 0x47D170..0x48D170, so they must not take a %gp_rel relocation.
 * An INCOMPLETE array type is what gives them `lui %hi` + `addiu %lo`.
 *
 * ⚠ The default of the inner switch calls this function RECURSIVELY with
 * kind 3 and then sets the sub-kind to 6; it does not fall into the tail.
 */

typedef struct Style {
    u8  pad0[0xC];
    s32 fC;
    u8  pad10[0x9C];
} Style;

typedef struct Layout {
    s32 f0;
    s32 f4;
    u8  pad8[8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[0x14];
} Layout;

typedef struct Panel {
    u8   pad0[0x70];
    s16  f70;
    u8   f72;
    u8   pad73;
    s16 *f74;
    u8   pad78[0xC];
    void *f84;
} Panel;

extern void *D_00484A70;
extern u8 factory_D_0050CC38[];
extern u8 factory_D_0050FED0[];

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

extern void factory_FactoryProduceShowMessage_4f62d0(Panel *o, s16 kind);

static inline void endBox(Layout *lay)
{
    lay->f10 = 0x1E;
    lay->f14 = 0x13;
    lay->f18 = 0xF;
    lay->f1C = 0xB;
    UiWindowFitToText_28d0c0(lay, 0, 0, 0);
}

void factory_FactoryProduceShowMessage_4f62d0(Panel *o, s16 kind)
{
    Layout lay __attribute__((aligned(16)));
    Style sty __attribute__((aligned(16)));
    s32 w;
    s32 h;
    s32 cx;
    s32 cy;
    s32 x;
    s32 y;
    s32 ty;

    memset(&lay, 0, 0x34);
    lay.f0 = ((s32)UiGetWidgetSprite_28fe10(o->f84, 0x8B, 0));
    lay.f4 = ((s32)UiGetWidgetText_28f620(o->f84, 0x8B, 0));
    MsgFormatParamsCtor_28aa00(&sty);
    memset(&sty, 0, 0xAC);
    UiSetTextString_28f510(o->f84, 0x8B, factory_D_0050CC38, 0);
    UiSetTextString_28f510(o->f84, 0x8E, factory_D_0050CC38, 0);

    switch (kind) {
    case 0:
        sty.fC = *o->f74;
        memset(factory_D_0050FED0, 0, 0x40);
        MsgFormat_28a9a0(factory_D_0050FED0, MsgTableLookup_28aa30(D_00484A70, 0x22), &sty, 1);
        UiSetTextString_28f510(o->f84, 0x8B, factory_D_0050FED0, 0);
        UiSetTextString_28f510(o->f84, 0x8E, MsgTableLookup_28aa30(D_00484A70, 0x1E), 0);
        w = UiGetWidgetTextWidth_28f400(o->f84, 0x8B, 0) + 0x3C;
        h = UiGetWidgetTextWidth_28f400(o->f84, 0x8E, 0);
        if (w < h) {
            lay.f10 = (h - w) + 0x5A;
        } else {
            lay.f10 = 0x5A;
        }
        lay.f14 = 0x35;
        lay.f18 = 0x4E;
        lay.f1C = 0xE;
        cx = lay.f10 + UiGetWidgetTextWidth_28f400(o->f84, 0x8B, 0);
        cy = lay.f14 + UiGetWidgetTextHeight_28f3d0(o->f84, 0x8B, 0);
        x = 0x100 - cx / 2;
        y = 0xE0 - cy / 2;
        UiSetSpritePos_28fd10(o->f84, 0x8E, x + 0x17, y + 8, 0);
        UiSetSpritePos_28fd10(o->f84, 0x8F, x + 0x1D, y + 0xF, 0);
        UiSetSpritePos_28fd10(o->f84, 0x90, x + 0x1D, y + 0xF, 0);
        UiSetTextPos_28f5d0(o->f84, 0x8E, x + 0x12, y + 0x46, 0);
        ty = y + (cy - lay.f14) + 0xF;
        UiSetSpritePosSize_28fd70(o->f84, 0x8D, x + 0xA, ty, 0xA, 6, 0);
        UiSetSpritePosSize_28fd70(o->f84, 0x8D, x + 0x14, ty, cx - 0x2A, 6, 1);
        UiSetSpritePosSize_28fd70(o->f84, 0x8D, x + 8 + (cx - 0x1E), ty, 0xA, 6, 2);
        UiWindowFitToText_28d0c0(&lay, 0, 0, 0);
        break;

    case 1:
        sty.fC = *o->f74;
        memset(factory_D_0050FED0, 0, 0x40);
        MsgFormat_28a9a0(factory_D_0050FED0, MsgTableLookup_28aa30(D_00484A70, 0xB4), &sty, 1);
        UiSetTextString_28f510(o->f84, 0x8B, factory_D_0050FED0, 0);
        StreamPlayMwv_207340(0x321, 0, 1.0f);
        endBox(&lay);
        break;

    case 2:
        sty.fC = *o->f74;
        memset(factory_D_0050FED0, 0, 0x40);
        MsgFormat_28a9a0(factory_D_0050FED0, MsgTableLookup_28aa30(D_00484A70, 0x20), &sty, 1);
        UiSetTextString_28f510(o->f84, 0x8B, factory_D_0050FED0, 0);
        StreamPlayMwv_207340(0x321, 0, 1.0f);
        endBox(&lay);
        break;

    case 3:
        sty.fC = *o->f74;
        memset(factory_D_0050FED0, 0, 0x40);
        MsgFormat_28a9a0(factory_D_0050FED0, MsgTableLookup_28aa30(D_00484A70, 0x21), &sty, 1);
        UiSetTextString_28f510(o->f84, 0x8B, factory_D_0050FED0, 0);
        endBox(&lay);
        break;

    case 4:
        switch (o->f70) {
        case 8:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7532), 0);
            break;
        case 9:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7530), 0);
            break;
        case 10:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7533), 0);
            break;
        case 11:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7531), 0);
            break;
        case 12:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x753B), 0);
            break;
        case 13:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x753C), 0);
            break;
        case 14:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x753A), 0);
            break;
        case 15:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7534), 0);
            break;
        case 16:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7535), 0);
            break;
        case 17:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7536), 0);
            break;
        case 19:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7537), 0);
            break;
        case 20:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7538), 0);
            break;
        case 21:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x7539), 0);
            break;
        case 18:
            UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x753D), 0);
            break;
        default:
            factory_FactoryProduceShowMessage_4f62d0(o, 3);
            o->f72 = 6;
            return;
        }
        endBox(&lay);
        break;

    case 5:
        UiSetTextString_28f510(o->f84, 0x8B, MsgTableLookup_28aa30(D_00484A70, 0x1F), 0);
        endBox(&lay);
        break;
    }
}
