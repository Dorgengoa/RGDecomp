/* rg-override: replaces game/src/main/math/AngleDiffSign_13c0d0.c sha256 b8b776cbb50c62cf383a88a9723f5639f99280d026e785c1555411af13816047
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* gp-relative constants (gp = 0x00485170); retail values in comments */
extern f32 D_0047D1FC; /* -0x7F74(gp) =  pi */
extern f32 D_0047D314; /* -0x7E5C(gp) = -pi */
extern f32 D_0047D318; /* -0x7E58(gp) = 2pi */
extern f32 D_0047D31C; /* -0x7E54(gp) = -pi */
extern f32 D_0047D320; /* -0x7E50(gp) = 2pi */

/* d = a - b wrapped into (-pi, pi]; returns 0 when d == 0, 1 when d > tol,
   -1 when d < -tol, else 0. */
s32 AngleDiffSign_13c0d0(f32 a, f32 b, f32 tol)
{
    f32 d = a - b;                    /* sub.s $f1, $f12, $f13 */
    f32 lim;

    if (0.0f == d)                    /* c.eq.s $f0(0), $f1; bc1fl */
        return 0;
    if (d <= D_0047D1FC) {            /* c.le.s; bc1tl (slot: lim = D_0047D314) */
        lim = D_0047D314;
    } else {
        d = d - D_0047D318;
        lim = D_0047D31C;
    }
    if (d < lim)                      /* c.lt.s; bc1f */
        d = d + D_0047D320;
    if (!(d <= tol))                  /* c.le.s $f1, $f14; bc1tl */
        return 1;
    if (d < -tol)                     /* neg.s (slot); c.lt.s; bc1t */
        return -1;                    /* andi 0xFF; negu */
    return 0;
}
