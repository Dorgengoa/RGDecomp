/* rgp:protos */
#define RGP_SELF_title_TitleMenuFadeOut_4ecd40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004ECD40 -- BYTE-IDENTICAL (session 12).
 *
 * One call: func_290690(o->field004, 1, 0.0f, -0.1f, -1.0f).  Three
 * float arguments, and the middle one is the pool constant.
 *
 * ⚠ HISTORY, because this unit was parked for five sessions on a WRONG cause.
 * It read `extern f32 D_0047D574 (-0.1f)` and sat at 2 bad word(s), recorded as a
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

typedef struct Obj_title_FUN_004ecd40 {
    u8 pad000[0x4];
    void *field004;    /* +0x4 */
} Obj_title_FUN_004ecd40;

/*rgp*/

s32 title_TitleMenuFadeOut_4ecd40(Obj_title_FUN_004ecd40 *o)
{
    UiFadeWidgetAlpha_290690(o->field004, 1, 0.0f, -0.1f, -1.0f);
    return 1;
}
