/* rgp:protos */
#define RGP_SELF_MtxMulPoint_13c890 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Matrix times vector, VU0 macro mode: one `vmulax` and three `vmadd`s down
   the accumulator. The VECTOR is loaded FIRST here and the matrix rows after
   it -- MtxMulVec4_10a8c0 does the same arithmetic with the loads the other way
   round and different registers, which is what says they are two hand-written
   routines rather than one inlined twice. */

void MtxMulPoint_13c890(Vec4 *pd, const Mtx4 *pm, const Vec4 *pv)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(16, (char *)(pv)); /* lqc2         vf16, 0(pv) */
rg_vu0_lqc2(10, (char *)(pm)); /* lqc2         vf10, 0(pm) */
rg_vu0_lqc2(11, (char *)(pm) + 0x10); /* lqc2         vf11, 0x10(pm) */
rg_vu0_lqc2(12, (char *)(pm) + 0x20); /* lqc2         vf12, 0x20(pm) */
rg_vu0_lqc2(13, (char *)(pm) + 0x30); /* lqc2         vf13, 0x30(pm) */
rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 10, 16, RG_BC_X); /* vmulax.xyzw  ACC, vf10, vf16x */
rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 16, RG_BC_Y); /* vmadday.xyzw ACC, vf11, vf16y */
rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 12, 16, RG_BC_Z); /* vmaddaz.xyzw ACC, vf12, vf16z */
rg_vu0_fmac(RG_VMADD, RG_XYZW, 17, 13, 0, RG_BC_W); /* vmaddw.xyzw  vf17, vf13, vf0w */
rg_vu0_sqc2(17, (char *)(pd)); /* sqc2         vf17, 0(pd) */
}
}
