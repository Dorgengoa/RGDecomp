/* rgp:protos */
#define RGP_SELF_VecAddInPlace_13e070 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* In-place Vec4 add: `*pa += *pb`. The destination is the first argument and
   is also the left operand, which is why this is a separate routine from
   VecAdd_13be20 rather than a call to it with pd == pa. */

void VecAddInPlace_13e070(Vec4 *pa, const Vec4 *pb)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(15, (char *)(pa)); /* lqc2      vf15, 0(pa) */
rg_vu0_lqc2(16, (char *)(pb)); /* lqc2      vf16, 0(pb) */
rg_vu0_fmac(RG_VADD, RG_XYZW, 15, 15, 16, RG_BC_NONE); /* vadd.xyzw vf15, vf15, vf16 */
rg_vu0_sqc2(15, (char *)(pa)); /* sqc2      vf15, 0(pa) */
}
}
