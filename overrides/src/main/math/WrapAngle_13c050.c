/* rg-override: replaces game/src/main/math/WrapAngle_13c050.c sha256 08513e5baa426f74010744d933ae6b6f37010d39deeb43fc90ed26c4854e22cd
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* gp-relative constants (gp = 0x00485170) */
extern f32 D_0047D1E4; /* -0x7F8C(gp) */
extern f32 D_0047D1FC; /* -0x7F74(gp) = pi */
extern f32 D_0047D230; /* -0x7F40(gp) */
extern f32 D_0047D234; /* -0x7F3C(gp) */
extern f32 D_0047D238; /* -0x7F38(gp) */
extern f32 D_0047D23C; /* -0x7F34(gp) */

f32 WrapAngle_13c050(f32 x)
{
    f32 p, q;

    if (x < D_0047D1FC) {             /* c.lt.s x, pi; bc1fl (slot: p = D_0047D1E4) */
        if (x <= D_0047D230)          /* c.le.s x, D_0047D230; bc1t */
            p = D_0047D234;
        else
            return x;                 /* b out; mov.s $f0, x */
    } else {
        p = D_0047D1E4;
    }
    /* mtc1 $0,$f0; adda.s $f0,$f12 (ACC = 0 + x); div.s; cvt.w.s (truncate);
       cvt.s.w; msub.s $f12 = ACC - p * q */
    q = (f32)(s32)(x / p);
    x = (0.0f + x) - p * q;
    if (!(x <= D_0047D1FC))           /* c.le.s; bc1tl (slot loads D_0047D238) */
        x = x - p;
    if (x < D_0047D238)               /* c.lt.s; bc1fl return x */
        x = x + D_0047D23C;
    return x;
}
