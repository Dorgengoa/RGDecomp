/* rgp:protos */
#define RGP_SELF_title_TitleLoadSlotCursorBob_4edcf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDCF0 -- BYTE-IDENTICAL (session 12).
 *
 * Advance a free-running phase by pi/40, wrap it past pi, and draw.  Twin of
 * 0x004E9F00, which needs two pragmas this one does not.
 *
 * ⚠ HISTORY, because this unit was parked for five sessions on a WRONG cause.
 * It read `extern f32 D_0047D3B8 / 0047D1FC (pi/40 and pi)` and sat at 8 bad word(s), recorded as a
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

typedef struct Obj_title_FUN_004edcf0 {
    s16 field000;      /* +0x0  */
    s16 field002;      /* +0x2  */
    s16 field004;      /* +0x4  */
    s16 field006;      /* +0x6  */
    u8 pad008[0x8];
    s16 field010;      /* +0x10 */
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004edcf0;

extern f32 D_004841F4;

/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadSlotCursorBob_4edcf0(Obj_title_FUN_004edcf0 *o, void *p, s32 mode)
{
    f32 t;
    f32 step;
    f32 k;
    s32 x;
    s32 y;

    step = 0.078539819f;
    t = D_004841F4 + step;
    D_004841F4 = t;
    if (t > 0.0f) {
        D_004841F4 = t - 3.1415927f;
    }
    k = 6.0f * Sinf_128fd0(D_004841F4);
    x = (s32)(k + (f32)(o->field000 + o->field010 * o->field004));
    y = o->field002 + o->field012 * o->field006;
    if (mode != 0) {
        UiSetWidgetPos_290f60(p, 0x43, x, y);
    } else {
        UiMoveWidgetUniform_290f50(p, 0x43, x, y, 0.5f, 0);
    }
    return 1;
}
