/* rgp:protos */
#define RGP_SELF_VecAdd_13be20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Vec4 add, VU0 macro mode. Four instructions and mwcc sinks the `sqc2` into
   the `jr`'s delay slot, which is what makes the five-word form come out
   exact. Written as assembly because COP2 is not expressible in C at all --
   the criterion the tree already set for earning a transcription. */

void VecAdd_13be20(Vec4 *pd, const Vec4 *pa, const Vec4 *pb)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(4, (char *)(pa)); /* lqc2      vf4, 0(pa) */
rg_vu0_lqc2(5, (char *)(pb)); /* lqc2      vf5, 0(pb) */
rg_vu0_fmac(RG_VADD, RG_XYZW, 6, 4, 5, RG_BC_NONE); /* vadd.xyzw vf6, vf4, vf5 */
rg_vu0_sqc2(6, (char *)(pd)); /* sqc2      vf6, 0(pd) */
}
}
