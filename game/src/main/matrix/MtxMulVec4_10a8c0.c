/* rgp:protos */
#define RGP_SELF_MtxMulVec4_10a8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Matrix times vector -- the other one. Same accumulator chain as
   MtxMulPoint_13c890 but the matrix rows load first, the vector last, the registers
   are vf4..vf9 instead of vf10..vf17, and the final `vmaddw` takes its w from
   the VECTOR rather than from vf0. That last difference is real arithmetic:
   this one uses v.w, MtxMulPoint_13c890 forces w to 1. */

void MtxMulVec4_10a8c0(Vec4 *pd, const Mtx4 *pm, const Vec4 *pv)
{ RG_VU0_FRAME;
    { /* [port] vu0asm: asm block -> VU0 model */
rg_vu0_lqc2(4, (char *)(pm)); /* lqc2         vf4, 0(pm) */
rg_vu0_lqc2(5, (char *)(pm) + 0x10); /* lqc2         vf5, 0x10(pm) */
rg_vu0_lqc2(6, (char *)(pm) + 0x20); /* lqc2         vf6, 0x20(pm) */
rg_vu0_lqc2(7, (char *)(pm) + 0x30); /* lqc2         vf7, 0x30(pm) */
rg_vu0_lqc2(8, (char *)(pv)); /* lqc2         vf8, 0(pv) */
rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 8, RG_BC_X); /* vmulax.xyzw  ACC, vf4, vf8x */
rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 8, RG_BC_Y); /* vmadday.xyzw ACC, vf5, vf8y */
rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 6, 8, RG_BC_Z); /* vmaddaz.xyzw ACC, vf6, vf8z */
rg_vu0_fmac(RG_VMADD, RG_XYZW, 9, 7, 8, RG_BC_W); /* vmaddw.xyzw  vf9, vf7, vf8w */
rg_vu0_sqc2(9, (char *)(pd)); /* sqc2         vf9, 0(pd) */
}
}
