/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsStateClose_4ecbf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004ECBF0 -- the confirm-dialog tick for one panel:
 * on the opening tick fade the window in and clear the latch, then poll the
 * widget and, on the accept code, latch, close both windows and play the
 * cursor sound.  292 bytes, 73 instructions, 4 conditional branches, 9 calls.
 *
 * * A four-member family found by ranking the OPEN population against ITSELF:
 * `004ED020` (0.871), `004EE7D0` (0.865) and `004EF800` (0.861) are the same
 * function over other panels.  The already-written `factory_FactoryBlueprintViewClose_4eef80` is
 * the same shape again and is PARKED on a tail-merge tie-break, so the whole
 * family's epilogue was checked here before anything else -- these four share
 * ONE `return 1` reached by a `b` from the latch guard AND by fall-through,
 * with `ld $31` duplicated, which is the arrangement mwcc picks by default.
 *
 * * The first parameter is never read; the opening flag arrives in `$5`.
 *
 * * `-0x724` is `D_00484A4C`, four bytes from `004eef80`'s `-0x728`
 * `D_00484A48`.  Recompute `_gp - offset` rather than copying the sibling's
 * symbol -- `_gp` is 0x00485170.
 *
 * !! UNPARKED by lane fy02.  The residue was the epilogue tail-merge, and the
 * key is lane fy01's: the `beql $2,$0` guard sits exactly TWO rows above
 * `b .L004ECCFC / ld $31,0x30($29)` (an EMPTY fall-through), which is a
 * one-arm `switch` with ONE trailing `return 1`, not the early `return 1;`
 * this file used to spell.  The header's claim that the duplicated `ld $31`
 * "is the arrangement mwcc picks by default" is OVERTURNED -- it is what mwcc
 * picks for a `switch`, and the early return inverts the shared epilogue.
 *
 * * The THREE context loads are emitted in a LEFT ROTATION of source
 * assignment order, not a reversal: source 0x8C, 0x94, 0x90 gives retail's
 * 0x94, 0x90, then 0x8C riding the `beqz $5` delay slot.  Measured: writing
 * them 0x8C, 0x90, 0x94 (the naive "reverse") emits 0x90, 0x94, 0x8C and is
 * exactly 2 bad words.  For n=2 the rotation and the reversal coincide, which
 * is why the two-field members read as "reverse source order".
 */

typedef struct Glyph {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Glyph;

typedef struct Ctx {
    u8    pad00[0x8C];
    void *f8C;
    void *f90;
    void *f94;
} Ctx;

extern Ctx *D_00484A4C;                         /* _gp - 0x724  */
extern s32  D_00484ABC;                         /* _gp - 0x6B4  */
extern f32  D_0047D4E4;                         /* _gp - 0x7C8C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryPartsStateClose_4ecbf0(s32 unused, s32 start)
{
    Glyph *g;
    void  *h;
    void  *w;
    void  *m;
    s32    a;
    s32    b;

    h = D_00484A4C->f8C;
    w = D_00484A4C->f94;
    m = D_00484A4C->f90;
    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        UiMoveWidgetUniform_290f50(h, 0x41, 0x200, 0x36, D_0047D4E4, 0);
        UiFadeWidgetAlpha_290690(h, 0x41, 0.0f, -0.125f, -1.0f);
        D_00484ABC = 0;
    }
    switch (D_00484ABC) {
    case 0:
        UiGetWidgetPos_2910a0(h, 0xC, &a, &b);
        if (a == -0xAA) {
            if (b == 0) {
                D_00484ABC = -1;
                StateMachineSetState_28ede0(w, 0x88CC, 0);
                UiSetWidgetVisible_290010(h, 0xC, 0, -1);
                UiSetWidgetVisible_290010(h, 0x41, 0, -1);
                g = ((Glyph *)UiEntryListFindByTag_28ea40(m, 0x88F4));
                FactoryPartsCursorSave_202f00(g->f16, g->f1A);
            }
        }
        break;
    }
    return 1;
}
