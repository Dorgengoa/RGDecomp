/* rg-override: replaces game/src/main/camera/AabbLoadToVu_13bfc0.c sha256 f8ab267254c63a90e5b4934c13d2bc39f667510ff645e8b962da0a5beffaf530
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
/* RG_VU0_LOCAL: the cross-file register protocol with AabbPlaneDistances_13bf50 /
   AabbLoadToVu_13bfc0 (vf7, vf10-12) shares the named context `xfbox` (docs/NATIVE-CPU.md) */
#define RG_VU0_CTX_NAME xfbox
#include "port/vu0_ctx.h"
#include "types.h"
extern u8 D_0047DE20[]; /* gp-0x7350: {0.5, 0, 0, 0} */
void AabbLoadToVu_13bfc0(const void *box, const void *m)
{
    rg_vu0_gpr_setp(3, (char *)(D_0047DE20) + 0); /* addiu      $3, $28, -0x7350 */
    rg_vu0_lqc2(3, rg_vu0_gptr(3)); /* lqc2       $vf3, 0x0($3) */
    rg_vu0_lqc2(1, (char *)(box)); /* lqc2       $vf1, 0x0($4) */
    rg_vu0_lqc2(2, (char *)(box) + 0x10); /* lqc2       $vf2, 0x10($4) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 3, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf3x */
    rg_vu0_fmac(RG_VMSUB, RG_XYZW, 5, 2, 3, RG_BC_X); /* vmsubx.xyzw $vf5, $vf2, $vf3x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 6, 5, 2, RG_BC_NONE); /* vadd.xyzw  $vf6, $vf5, $vf2 */
    rg_vu0_lqc2(10, (char *)(m)); /* lqc2       $vf10, 0x0($5) */
    rg_vu0_lqc2(11, (char *)(m) + 0x10); /* lqc2       $vf11, 0x10($5) */
    rg_vu0_lqc2(12, (char *)(m) + 0x20); /* lqc2       $vf12, 0x20($5) */
    rg_vu0_lqc2(13, (char *)(m) + 0x30); /* lqc2       $vf13, 0x30($5) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 10, 6, RG_BC_X); /* vmulax.xyzw $ACC, $vf10, $vf6x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 6, RG_BC_Y); /* vmadday.xyzw $ACC, $vf11, $vf6y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 12, 6, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf12, $vf6z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 7, 13, 0, RG_BC_W); /* vmaddw.xyzw $vf7, $vf13, $vf0w */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 10, 10, 5, RG_BC_X); /* vmulx.xyzw $vf10, $vf10, $vf5x */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 11, 11, 5, RG_BC_Y); /* vmuly.xyzw $vf11, $vf11, $vf5y */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 12, 12, 5, RG_BC_Z); /* vmulz.xyzw $vf12, $vf12, $vf5z */
}
