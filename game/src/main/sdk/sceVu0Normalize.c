/* rgp:protos */
#define RGP_SELF_sceVu0Normalize 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of VecNormalize_13bd90 (byte-identical, in cunits):
   normalise xyz through VU0's Q register. */

void sceVu0Normalize(Vec4 *pd, const Vec4 *pv)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(4, (char *)(pv)); /* lqc2       vf4, 0(pv) */
rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 4, RG_BC_NONE); /* vmul.xyz   vf5, vf4, vf4 */
rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y); /* vaddy.x    vf5, vf5, vf5y */
rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z); /* vaddz.x    vf5, vf5, vf5z */
rg_vu0_sqrt(5, RG_BC_X); /* vsqrt      Q, vf5x */
/* vwaitq */
rg_vu0_fmac(RG_VADD, RG_X, 5, 0, RG_FT_Q, RG_BC_NONE); /* vaddq.x    vf5, vf0, Q */
/* vnop */
/* vnop */
rg_vu0_div(0, RG_BC_W, 5, RG_BC_X); /* vdiv       Q, vf0w, vf5x */
rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 0, 0, RG_BC_NONE); /* vsub.xyzw  vf6, vf0, vf0 */
/* vwaitq */
rg_vu0_fmac(RG_VMUL, RG_XYZ, 6, 4, RG_FT_Q, RG_BC_NONE); /* vmulq.xyz  vf6, vf4, Q */
rg_vu0_sqc2(6, (char *)(pd)); /* sqc2       vf6, 0(pd) */
}
}
