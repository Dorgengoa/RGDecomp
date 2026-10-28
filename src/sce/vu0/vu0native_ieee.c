/* SPDX-License-Identifier: CC0-1.0 */
/* rg-vu0native-tests `ieee`: the native float rules (built with RG_VU0_LOCAL
 * and RG_VU0_IEEE, as RG_VU0_MODE=native builds game code). */
#include <stdio.h>

#include "port/vu0.h"

#ifndef RG_VU0_IEEE
#error "vu0native_ieee.c must be built with RG_VU0_IEEE"
#endif

#define CHK(c, msg) do { if (!(c)) { fails++; printf("FAIL ieee: %s\n", msg); } } while (0)

int vni_check(int wrong)
{ RG_VU0_FRAME;
    int fails = 0;
    float v[4] __attribute__((aligned(16))) = {1.0f, -2.0f, 0.0f, 3.0f};
    float o[4] __attribute__((aligned(16)));
    /* round to nearest: 1 + 2^-24 * 3 rounds up (VU chop would give 1 + 2^-23) */
    CHK(rg_u2f(rg_vu_addf(rg_f2u(1.0f), rg_f2u(1.7881393e-07f))) == 1.0000002f, "round to nearest");
    /* x / 0 = +-max with the xor sign */
    CHK(rg_vu_divf(rg_f2u(1.0f), rg_f2u(0.0f)) == 0x7FFFFFFFu, "1/0");
    CHK(rg_vu_divf(rg_f2u(-1.0f), rg_f2u(0.0f)) == 0xFFFFFFFFu, "-1/0");
    CHK(rg_vu_divf(rg_f2u(1.0f), rg_f2u(-0.0f)) == 0xFFFFFFFFu, "1/-0");
    /* the VU round-to-integer idiom keeps chop rounding (VecWrapAngle, VecSinCos):
       2.7 + 1.5*2^23 - 1.5*2^23 = 2 (IEEE nearest would give 3) */
    CHK(rg_u2f(rg_vu_subf(rg_vu_addf(rg_f2u(2.7f), 0x4B400000u), 0x4B400000u)) == 2.0f, "magic round");
    CHK(rg_u2f(rg_vu_addf(rg_vu_subf(rg_f2u(-2.7f), 0x4B400000u), 0x4B400000u)) == -2.0f, "magic round neg");
    /* non-finite results and exponent-255 inputs follow the VU (clamp to +-max) */
    CHK(rg_vu_mulf(0x7F7FFFFFu, rg_f2u(2.0f)) == 0x7FFFFFFFu, "overflow clamps");
    CHK(rg_vu_mulf(0x7FFFFFFFu, rg_f2u(0.5f)) == 0x7F7FFFFFu, "VU max is a number");
    CHK(rg_vu_subf(0x7FFFFFFFu, 0x7FFFFFFFu) == 0, "max - max = 0");
    CHK(rg_vu_divf(rg_f2u(1.0f), 0x00000001u) == 0x7FFFFFFFu, "1 / denormal");
    /* sqrt takes |x| */
    CHK(rg_u2f(rg_vu_sqrtf(rg_f2u(-4.0f))) == 2.0f, "sqrt(-4)");
    /* register ops on the function's own file (RG_VU0_FRAME) */
    rg_vu0_lqc2(4, v);
    rg_vu0_ftoi(0, RG_XYZW, 5, 4);
    rg_vu0_sqc2(5, o);
    CHK(((int *)o)[1] == -2 && ((int *)o)[3] == 3, "ftoi0");
    v[0] = 3.0e9f;
    rg_vu0_lqc2(4, v);
    rg_vu0_ftoi(4, RG_X, 5, 4);
    rg_vu0_sqc2(5, o);
    CHK(((int *)o)[0] == 0x7FFFFFFF, "ftoi saturation");
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 4, RG_BC_W);  /* v * v.w */
    rg_vu0_sqc2(6, o);
    CHK(o[1] == (wrong ? 0.0f : -6.0f) && o[3] == 9.0f, "vmulw");
    CHK(RG_VU0_IS_LOCAL == 1, "RG_VU0_LOCAL");
    return fails;
}
