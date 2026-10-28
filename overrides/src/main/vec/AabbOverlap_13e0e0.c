/* rg-override: replaces game/src/main/vec/AabbOverlap_13e0e0.c sha256 57154cd39c471694afce5e45192fc1efc5131c465b215c1cce8a595899bff280
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

/* 1 when every xyz lane of (a - d) and (c - b) is non-negative. */
s32 AabbOverlap_13e0e0(const void *a, const void *b, const void *c, const void *d)
{ RG_VU0_FRAME;
    int ss;
    rg_vu0_lqc2(10, a);                                  /* lqc2 vf10, 0($4) */
    rg_vu0_lqc2(11, b);                                  /* lqc2 vf11, 0($5) */
    rg_vu0_lqc2(1, c);                                   /* lqc2 vf1, 0($6) */
    rg_vu0_lqc2(2, d);                                   /* lqc2 vf2, 0($7) */
    ss = 0;                                              /* ctc2 $0, vi16 */
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 25, 10, 2, RG_BC_NONE); /* vsub.xyz vf25, vf10, vf2 */
    ss |= rg_sign_xyz(&rg_vu0, 25);
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 25, 1, 11, RG_BC_NONE); /* vsub.xyz vf25, vf1, vf11 */
    ss |= rg_sign_xyz(&rg_vu0, 25);
    /* cfc2 $2, vi16; andi $2, $2, 0x80; xor $2, $2, $0; sltiu $2, $2, 1 */
    return ss == 0;
}
