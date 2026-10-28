/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintShowProduct_4f9130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F9130 -- fill the item-detail card and pick its
 * gauge style.  588 bytes, 148 instructions, 4 conditional branches, 22 calls
 * (br/ins 0.027): the branch-light band.
 *
 * ★ factory_D_0050FF70 is OVERLAY data at 0x50xxxx, far outside the gp window
 * (_gp 0x00485170 +/- 0x8000), so it is an INCOMPLETE array and takes %hi/%lo.
 * D_00484A70 (_gp - 0x700) is inside the window and stays plain.
 *
 * ★ The dispatch re-tests 0xC and 0xF after the `k == 0xC || k == 0xF` guard
 * because the source really does nest a second `if`/`else if` inside it -- the
 * duplicated `addiu $2, $0, 0xC` in the first `beql`'s delay slot is the
 * likely-branch duplication of the merge's first instruction, not a switch.
 */

typedef struct Rec {
    s16   f00;
    u8    pad02[0x2A];
    s16   f2C;
    u8    pad2E[0x2];
    void *f30;
} Rec;

typedef struct Ent {
    u8    pad00[0x4];
    Rec  *f04;
    u8    pad08[0x8];
    void *f10;
} Ent;

typedef struct Obj { u8 pad00[0x80]; void *f80; } Obj;

typedef struct Buf { u8 pad00[0xC]; s32 f0C; u8 pad10[0x9C]; } Buf;   /* 0xAC */

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    factory_D_0050FF70[];

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

void factory_FactoryBlueprintShowProduct_4f9130(Obj *o, Ent *e)
{
    Buf buf __attribute__((aligned(16)));
    s32 t;
    s32 k;

    MsgFormatParamsCtor_28aa00(&buf);
    memset(&buf, 0, 0xAC);
    buf.f0C = e->f04->f00;
    memset(factory_D_0050FF70, 0, 0x80);
    MsgFormat_28a9a0(factory_D_0050FF70, MsgTableLookup_28aa30(D_00484A70, 0x22), &buf, 1);
    UiSetTextString_28f510(o->f80, 0x3A, factory_D_0050FF70, 1);
    UiSetTextString_28f510(o->f80, 0x3A, e->f04->f30, 2);
    t = UiGetWidgetTextWidth_28f400(o->f80, 0x3A, 3);
    UiSetTextX_28f590(o->f80, 0x3A, t + 0xA, 4);
    UiSetTextString_28f510(o->f80, 0x3A, e->f10, 4);
    UiSetWidgetVisible_290010(o->f80, 0x3E, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x3F, 0, -1);
    UiSetSpriteFlags_290bd0(o->f80, 0x3E, (long long)(8), 0, 0, 0);
    UiSetSpriteFlags_290bd0(o->f80, 0x3F, (long long)(8), 0, 0, 0);
    k = e->f04->f2C;
    if (k == 0xC || k == 0xF) {
        if (k == 0xC) {
            UiSetSpriteSize_28fc30(o->f80, 0x3F, 0x28, 0x2D, 0);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x3F, 0x140, 0x20, 0x20, 0x20, 0);
        } else if (k == 0xF) {
            UiSetSpriteSize_28fc30(o->f80, 0x3F, 0x28, 0x2D, 0);
            UiSetSpriteUvRect_28f9d0(o->f80, 0x3F, 0x140, 0, 0x20, 0x20, 0);
        }
        UiSetWidgetVisible_290010(o->f80, 0x3F, 1, -1);
    } else {
        UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(o->f80, 0x3E, 0), k, 0x28, 0x2D);
        UiSetWidgetVisible_290010(o->f80, 0x3E, 1, -1);
    }
}
