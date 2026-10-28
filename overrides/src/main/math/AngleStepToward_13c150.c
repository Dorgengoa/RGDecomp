/* rg-override: replaces game/src/main/math/AngleStepToward_13c150.c sha256 38c91f8cd468ee952fff800728b6054c6ef67ec4a1d7a0aa06fa0e92514f6825
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* gp-relative constants (gp = 0x00485170); retail values in comments */
extern f32 D_0047D1FC; /* -0x7F74(gp) =  pi */
extern f32 D_0047D2F0; /* -0x7E80(gp) = -pi */
extern f32 D_0047D2F4; /* -0x7E7C(gp) = 2pi */
extern f32 D_0047D2F8; /* -0x7E78(gp) = -pi */
extern f32 D_0047D2FC; /* -0x7E74(gp) = 2pi */
extern f32 D_0047D300; /* -0x7E70(gp) = -pi */
extern f32 D_0047D304; /* -0x7E6C(gp) = 2pi */
extern f32 D_0047D308; /* -0x7E68(gp) = -pi */
extern f32 D_0047D30C; /* -0x7E64(gp) = 2pi */

/* Step angle cur toward tgt.  mode 0: by +-step (snaps to tgt when within
   step); mode 1: by (wrapped diff) / step; any other mode: no step.  The
   result is wrapped once more. */
f32 AngleStepToward_13c150(f32 cur, f32 tgt, f32 step, s32 mode)
{
    f32 d = tgt - cur;                /* sub.s $f2, $f13, $f12 */
    f32 lim, inc, r, ad;

    if (d <= D_0047D1FC) {            /* c.le.s; bc1tl (slot: lim = D_0047D2F0) */
        lim = D_0047D2F0;
    } else {
        d = d - D_0047D2F4;
        lim = D_0047D2F8;
    }
    if (d <= lim)                     /* c.le.s; bc1f */
        d = d + D_0047D2FC;
    inc = 0.0f;                       /* mtc1 $0, $f1 */
    if (mode == 0) {                  /* bnel $4, $0 (annulled slot) */
        if (d < inc)                  /* c.lt.s d, 0; bc1fl (slot: ad = d) */
            ad = -d;
        else
            ad = d;
        if (ad < step)                /* c.lt.s; bc1f */
            return tgt;
    }
    if (mode == 1) {                  /* beq $4, $2(=1) */
        inc = d / step;               /* div.s $f1, $f2, $f14 */
        goto add;
    }
    if (mode != 0) {                  /* beqz $4 */
        r = cur + inc;                /* b L230; add.s (slot) */
        goto wrap;
    }
    if (d < 0.0f) {                   /* c.lt.s; bc1f L1F8 */
        if (step < d)                 /* c.lt.s $f14, $f2; bc1fl (slot: inc -= step) */
            return tgt;
        inc = inc - step;
    }
    if (!(d < 0.0f)) {                /* c.lt.s; bc1t L22C */
        if (step <= d)                /* c.le.s; bc1tl (slot: inc += step) */
            inc = inc + step;
        else
            return tgt;
    }
add:
    r = cur + inc;                    /* add.s $f0, $f12, $f1 */
wrap:
    if (r <= D_0047D1FC) {            /* c.le.s; bc1tl (slot: lim = D_0047D300) */
        lim = D_0047D300;
    } else {
        r = r - D_0047D304;
        lim = D_0047D308;
    }
    if (r <= lim)                     /* c.le.s; bc1f */
        r = r + D_0047D30C;
    return r;
}
