/* rgp:protos */
#define RGP_SELF_VecSub_13be40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Vec4 subtract, the sibling of VecAdd_13be20 -- same four instructions with
   `vsub` in place of `vadd`. CameraTrackUpdate_305960.cpp already names the pair
   `a + b` and `a - b`. */

void VecSub_13be40(Vec4 *pd, const Vec4 *pa, const Vec4 *pb)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(4, (char *)(pa)); /* lqc2      vf4, 0(pa) */
rg_vu0_lqc2(5, (char *)(pb)); /* lqc2      vf5, 0(pb) */
rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 4, 5, RG_BC_NONE); /* vsub.xyzw vf6, vf4, vf5 */
rg_vu0_sqc2(6, (char *)(pd)); /* sqc2      vf6, 0(pd) */
}
}
