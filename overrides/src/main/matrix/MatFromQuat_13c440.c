/* rg-override: replaces game/src/main/matrix/MatFromQuat_13c440.c sha256 cd47273d2071550e2e31b5c1ddea073a33d91bfd17620aee7330646ae87ebf9d
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"
extern u8 D_0047DE10[]; /* gp-0x7360: {sqrt(2), 0, 0, 0} */
void MatFromQuat_13c440(void *d, const void *q)
{ RG_VU0_FRAME;
    rg_vu0_gpr_setp(3, (char *)(D_0047DE10) + 0); /* addiu      $3, $28, -0x7360 */
    rg_vu0_lqc2(10, (char *)(q)); /* lqc2       $vf10, 0x0($5) */
    rg_vu0_lqc2(2, rg_vu0_gptr(3)); /* lqc2       $vf2, 0x0($3) */
    rg_vu0_fmac(RG_VMULA, RG_XYZ, 0, 10, 10, RG_BC_NONE); /* vmula.xyz  $ACC, $vf10, $vf10 */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 11, 10, 2, RG_BC_X); /* vmulx.xyzw $vf11, $vf10, $vf2x */
    rg_vu0_mr32(RG_W, 15, 0); /* vmr32.w    $vf15, $vf0 */
    rg_vu0_mr32(RG_W, 16, 0); /* vmr32.w    $vf16, $vf0 */
    rg_vu0_mr32(RG_W, 17, 0); /* vmr32.w    $vf17, $vf0 */
    rg_vu0_fmac(RG_VMADD, RG_XYZ, 12, 10, 10, RG_BC_NONE); /* vmadd.xyz  $vf12, $vf10, $vf10 */
    rg_vu0_fmac(RG_VADD, RG_XYZ, 1, 0, 0, RG_BC_W); /* vaddw.xyz  $vf1, $vf0, $vf0w */
    rg_vu0_opmula(11, 11); /* vopmula.xyz $ACC, $vf11, $vf11 */
    rg_vu0_fmac(RG_VMSUB, RG_XYZ, 2, 11, 11, RG_BC_W); /* vmsubw.xyz $vf2, $vf11, $vf11w */
    rg_vu0_fmac(RG_VMADD, RG_XYZ, 3, 11, 11, RG_BC_W); /* vmaddw.xyz $vf3, $vf11, $vf11w */
    rg_vu0_fmac(RG_VADDA, RG_XYZ, 0, 0, 0, RG_BC_W); /* vaddaw.xyz $ACC, $vf0, $vf0w */
    rg_vu0_fmac(RG_VMSUBA, RG_YZ, 0, 1, 12, RG_BC_X); /* vmsubax.yz $ACC, $vf1, $vf12x */
    rg_vu0_fmac(RG_VMSUB, RG_Z, 17, 1, 12, RG_BC_Y); /* vmsuby.z   $vf17, $vf1, $vf12y */
    rg_vu0_fmac(RG_VMSUBA, RG_X, 0, 1, 12, RG_BC_Y); /* vmsubay.x  $ACC, $vf1, $vf12y */
    rg_vu0_fmac(RG_VMSUB, RG_Y, 16, 1, 12, RG_BC_Z); /* vmsubz.y   $vf16, $vf1, $vf12z */
    rg_vu0_mr32(RG_Y, 15, 2); /* vmr32.y    $vf15, $vf2 */
    rg_vu0_fmac(RG_VMSUB, RG_X, 15, 1, 12, RG_BC_Z); /* vmsubz.x   $vf15, $vf1, $vf12z */
    rg_vu0_mr32(RG_X, 17, 2); /* vmr32.x    $vf17, $vf2 */
    rg_vu0_fmac(RG_VADD, RG_Z, 15, 0, 3, RG_BC_Y); /* vaddy.z    $vf15, $vf0, $vf3y */
    rg_vu0_mr32(RG_W, 11, 2); /* vmr32.w    $vf11, $vf2 */
    rg_vu0_mr32(RG_Z, 16, 11); /* vmr32.z    $vf16, $vf11 */
    rg_vu0_fmac(RG_VADD, RG_Y, 17, 0, 3, RG_BC_X); /* vaddx.y    $vf17, $vf0, $vf3x */
    rg_vu0_mr32(RG_Y, 3, 3); /* vmr32.y    $vf3, $vf3 */
    rg_vu0_mr32(RG_X, 16, 3); /* vmr32.x    $vf16, $vf3 */
    rg_vu0_sqc2(15, (char *)(d)); /* sqc2       $vf15, 0x0($4) */
    rg_vu0_sqc2(16, (char *)(d) + 0x10); /* sqc2       $vf16, 0x10($4) */
    rg_vu0_sqc2(17, (char *)(d) + 0x20); /* sqc2      $vf17, 0x20($4) */
}
