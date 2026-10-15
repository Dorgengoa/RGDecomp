#include "types.h"

/* title.bin overlay, 0x004EFB90 -- BYTE-IDENTICAL (session 12).
 *
 * Seed a gp float, turn it into an integer pair through a helper, then hand
 * the pair to a draw call.  D_00484264 is taken by ADDRESS for the first
 * call and read as a FLOAT for the second, so it is one f32 global that
 * func_28B630 writes; `daddu $8, $7, $0` in the delay slot is the same
 * integer passed twice.
 *
 * ⚠ HISTORY, because this unit was parked for five sessions on a WRONG cause.
 * It read `extern f32 D_0047D3B8 (0.078539819f = pi/40)` and sat at 2 bad word(s), recorded as a
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

extern f32 D_00484264;
extern void *D_00484254;

extern void func_28B630(f32 v, f32 *p);
extern f32 func_128FD0(f32 v);
extern void func_28ECD0(void *a, s32 *x, s32 *y, s32 n, s32 m);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);

s32 title_TitleOptionsCursorBobCb_4efb90(void *o)
{
    s32 x;
    s32 y;
    s32 n;

    func_28B630(0.078539819f, &D_00484264);
    n = (s32)(6.0f * func_128FD0(D_00484264));
    func_28ECD0(o, &x, &y, n, n);
    func_290F50(D_00484254, 0x60, x, y, 0, 0.25f);
    return 1;
}
