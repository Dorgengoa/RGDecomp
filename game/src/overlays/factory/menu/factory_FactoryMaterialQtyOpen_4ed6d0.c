/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialQtyOpen_4ed6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004ED6D0 -- the per-tick handler for panel id 0x89B2
 * (dispatch table entry at main 0x00454FE4).  224 bytes, 56 instructions,
 * 3 conditional branches, 6 calls.
 *
 * SEED of the 004ED6D0 / 004EDC10 / 004EE360 twin family (948 B).
 *
 * * The first parameter is never read; the opening flag arrives in `$5`
 *   -- the same shape as `factory_FactoryPartsStateClose_4ecbf0`.
 * * The `w == 0` guard is the INVERTED early return: retail branches INTO the
 *   body (`bnez $16`) and lets the failure fall through to `b <epilogue>` with
 *   `daddu $2,$0,$0` in the slot.
 * * `D_0047D500` is 0.4f in mwcc's .lit4 pool (0x0047D1D0-0x0047D7FF); the
 *   neighbours spell pool entries as `extern f32`.
 * * The three `sh $0` stores happen through the RETURN VALUE of func_28EA40
 *   ($2 is caller-saved), so the call must be named in a local -- writing
 *   `func_28EA40(...)->f14 = 0;` three times would emit three calls.
 * * The tail guard is `>= 1.0f`: `c.lt.s $f0,$f1` + `bc1tl` PAST the body with
 *   the single `return 1` duplicated into the likely slot.
 */

typedef struct Glyph {
    u8  pad00[0xC];
    s16 f0C;
    u8  pad0E[0x6];
    s16 f14;
    s16 f16;
} Glyph;

typedef struct View {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    void *f48;
} View;

extern View *D_00484A58;                        /* _gp - 0x718  */
extern f32   D_0047D500;                        /* _gp - 0x7C70 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialQtyOpen_4ed6d0(s32 unused, s32 start)
{
    Glyph *g;
    void  *w;

    w = D_00484A58->f40;
    if (w == 0) {
        return 0;
    }
    if (start != 0) {
        UiSetWidgetVisible_290010(w, 0x77, 1, -1);
        UiSetWidgetAlpha_2907a0(w, 0x77, 0.0f);
        UiFadeWidgetAlpha_290690(w, 0x77, 1.0f, D_0047D500, -1.0f);
        factory_FactoryMaterialQtyPreset_4f2bf0(D_00484A58);
        g = ((Glyph *)UiEntryListFindByTag_28ea40(D_00484A58->f44, 0x8930));
        g->f14 = 0;
        g->f16 = 0;
        g->f0C = 0;
    }
    if (UiGetWidgetAlpha_290770(w, 0x77) >= 1.0f) {
        StateMachineSetState_28ede0(D_00484A58->f48, 0x89BC, 0);
    }
    return 1;
}
