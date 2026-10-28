/* rgp:protos */
#define RGP_SELF_VecScale_13be00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Vec4 times a scalar. The scalar arrives in $f12 and has to reach a VU
   register, so it goes out through `mfc1` into an integer register and back
   in through `qmtc2` -- there is no float path into COP2. The `nop` between
   them is the mfc1 result latency and is part of the routine.

   ★ The staging register is HARD-CODED to $8. Bound to a C local instead,
   mwcc allocates $3 -- the first caller-saved temp an allocator reaches for
   -- and the function misses by exactly those two words. $8 is $t0, which is
   what a human writing the routine by hand picks, and it is the same evidence
   the libvu0 files rest on: the register choice is content, not naming. */

void VecScale_13be00(Vec4 *pd, const Vec4 *pa, f32 s)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(4, (char *)(pa)); /* lqc2       vf4, 0(pa) */
rg_vu0_mfc1(8, (s)); /* mfc1       $8, s */
/* nop */
rg_vu0_qmtc2(8, 5); /* qmtc2.ni   $8, vf5 */
rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_X); /* vmulx.xyzw vf6, vf4, vf5x */
rg_vu0_sqc2(6, (char *)(pd)); /* sqc2       vf6, 0(pd) */
}
}
