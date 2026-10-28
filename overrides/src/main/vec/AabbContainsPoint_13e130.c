/* rg-override: replaces game/src/main/vec/AabbContainsPoint_13e130.c sha256 98b6bd110fe8a769bc04e24b416c8d3b4e0714d1f854b0059e21a795fa537a21
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* The VU0 model does not keep MAC/status flags (cfc2 vi16 reads 0), so the
   sticky sign flag (status bit 7, SS) these vsubs raise is computed here from
   the sign bits of the masked .xyz result lanes. */
static int rg_sign_xyz(rg_vu0_state *rg_vu0_p_, int vf)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    return (int)((rg_vu0.vf[vf].u[0] | rg_vu0.vf[vf].u[1] | rg_vu0.vf[vf].u[2]) >> 31);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* 1 when every xyz lane of (a - p) and (p - b) is non-negative. */
s32 AabbContainsPoint_13e130(const void *p, const void *a, const void *b)
{ RG_VU0_FRAME;
    int ss;
    rg_vu0_lqc2(1, p);                                   /* lqc2 vf1, 0($4) */
    rg_vu0_lqc2(10, a);                                  /* lqc2 vf10, 0($5) */
    rg_vu0_lqc2(11, b);                                  /* lqc2 vf11, 0($6) */
    ss = 0;                                              /* ctc2 $0, vi16 */
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 25, 10, 1, RG_BC_NONE); /* vsub.xyz vf25, vf10, vf1 */
    ss |= rg_sign_xyz(&rg_vu0, 25);
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 25, 1, 11, RG_BC_NONE); /* vsub.xyz vf25, vf1, vf11 */
    ss |= rg_sign_xyz(&rg_vu0, 25);
    /* cfc2 $2, vi16; andi $2, $2, 0x80; xor $2, $2, $0; sltiu $2, $2, 1 */
    return ss == 0;
}
