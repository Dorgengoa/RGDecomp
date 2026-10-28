/* rg-override: replaces game/src/main/camera/AabbPlaneDistances_13bf50.c sha256 7097262c40918e346d327f679668320f603f1553ea4e7afccf65764114cc3114
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
/* RG_VU0_LOCAL: the cross-file register protocol with AabbPlaneDistances_13bf50 /
   AabbLoadToVu_13bfc0 (vf7, vf10-12) shares the named context `xfbox` (docs/NATIVE-CPU.md) */
#define RG_VU0_CTX_NAME xfbox
#include "port/vu0_ctx.h"
#include "types.h"

void AabbPlaneDistances_13bf50(void *ext, void *dist, const void *planes)
{
    rg_vu0_lqc2(1, (char *)(planes)); /* lqc2       $vf1, 0x0($6) */
    rg_vu0_lqc2(2, (char *)(planes) + 0x10); /* lqc2       $vf2, 0x10($6) */
    rg_vu0_lqc2(3, (char *)(planes) + 0x20); /* lqc2       $vf3, 0x20($6) */
    rg_vu0_lqc2(4, (char *)(planes) + 0x30); /* lqc2       $vf4, 0x30($6) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 10, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf10x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 10, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf10y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 20, 3, 10, RG_BC_Z); /* vmaddz.xyzw $vf20, $vf3, $vf10z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 11, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf11x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 11, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf11y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 21, 3, 11, RG_BC_Z); /* vmaddz.xyzw $vf21, $vf3, $vf11z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 12, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf12x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 12, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf12y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 22, 3, 12, RG_BC_Z); /* vmaddz.xyzw $vf22, $vf3, $vf12z */
    rg_vu0_abs(RG_XYZW, 20, 20); /* vabs.xyzw  $vf20, $vf20 */
    rg_vu0_abs(RG_XYZW, 21, 21); /* vabs.xyzw  $vf21, $vf21 */
    rg_vu0_abs(RG_XYZW, 22, 22); /* vabs.xyzw  $vf22, $vf22 */
    rg_vu0_fmac(RG_VADDA, RG_XYZW, 0, 20, 21, RG_BC_NONE); /* vadda.xyzw $ACC, $vf20, $vf21 */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 25, 22, 0, RG_BC_W); /* vmaddw.xyzw $vf25, $vf22, $vf0w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 7, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf7x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 7, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf7y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 3, 7, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf3, $vf7z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 26, 4, 0, RG_BC_W); /* vmaddw.xyzw $vf26, $vf4, $vf0w */
    rg_vu0_sqc2(26, (char *)(dist)); /* sqc2       $vf26, 0x0($5) */
    rg_vu0_sqc2(25, (char *)(ext)); /* sqc2      $vf25, 0x0($4) */
}
