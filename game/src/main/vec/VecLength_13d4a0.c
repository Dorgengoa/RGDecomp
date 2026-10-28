/* rgp:protos */
#define RGP_SELF_VecLength_13d4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Length of a Vec4's xyz. The three squares are summed with two `vmr32`
   rotations rather than the `vaddy/vaddz` chain the quaternion dot product
   uses, and the square root comes back through VU0's Q register -- `vsqrt`,
   `vwaitq`, then `cfc2` out of $vi22 and `mtc1` into the float return.
   There is no path from Q to an FPR that does not go through a GPR. */

f32 VecLength_13d4a0(const Vec4 *pv)
{ RG_VU0_FRAME;
    f32 r;

    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(4, (char *)(pv)); /* lqc2     vf4, 0(pv) */
rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE); /* vmul.xyz vf4, vf4, vf4 */
rg_vu0_mr32(RG_XY, 5, 4); /* vmr32.xy vf5, vf4 */
rg_vu0_mr32(RG_X, 6, 5); /* vmr32.x  vf6, vf5 */
rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 5, RG_BC_NONE); /* vadd.x   vf7, vf4, vf5 */
rg_vu0_fmac(RG_VADD, RG_X, 5, 6, 7, RG_BC_NONE); /* vadd.x   vf5, vf6, vf7 */
rg_vu0_sqrt(5, RG_BC_X); /* vsqrt    Q, vf5x */
/* vwaitq */
rg_vu0_cfc2(2, 22); /* cfc2.ni  $2, $vi22 */
(r) = rg_vu0_mtc1(2); /* mtc1     $2, r */
}
    return r;
}
