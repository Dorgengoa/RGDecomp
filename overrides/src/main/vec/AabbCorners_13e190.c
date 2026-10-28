/* rg-override: replaces game/src/main/vec/AabbCorners_13e190.c sha256 48f69987601abe5c3ca8a680640e7641a778a23b919a557f44a3074628199372
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void AabbCorners_13e190(void *d, const void *lo, const void *hi)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(1, (char *)(lo)); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)(hi)); /* lqc2       $vf2, 0x0($6) */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 3, 2, 0, RG_BC_X); /* vaddx.xyzw $vf3, $vf2, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 4, 2, 0, RG_BC_X); /* vaddx.xyzw $vf4, $vf2, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 5, 2, 0, RG_BC_X); /* vaddx.xyzw $vf5, $vf2, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 6, 1, 0, RG_BC_X); /* vaddx.xyzw $vf6, $vf1, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 7, 1, 0, RG_BC_X); /* vaddx.xyzw $vf7, $vf1, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 8, 1, 0, RG_BC_X); /* vaddx.xyzw $vf8, $vf1, $vf0x */
    rg_vu0_sqc2(2, (char *)(d)); /* sqc2       $vf2, 0x0($4) */
    rg_vu0_sqc2(1, (char *)(d) + 0x70); /* sqc2       $vf1, 0x70($4) */
    rg_vu0_fmac(RG_VADD, RG_X, 3, 1, 0, RG_BC_X); /* vaddx.x    $vf3, $vf1, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_Y, 4, 1, 0, RG_BC_X); /* vaddx.y    $vf4, $vf1, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_Z, 5, 1, 0, RG_BC_X); /* vaddx.z    $vf5, $vf1, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_X, 6, 2, 0, RG_BC_X); /* vaddx.x    $vf6, $vf2, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_Y, 7, 2, 0, RG_BC_X); /* vaddx.y    $vf7, $vf2, $vf0x */
    rg_vu0_fmac(RG_VADD, RG_Z, 8, 2, 0, RG_BC_X); /* vaddx.z    $vf8, $vf2, $vf0x */
    rg_vu0_sqc2(3, (char *)(d) + 0x10); /* sqc2       $vf3, 0x10($4) */
    rg_vu0_sqc2(4, (char *)(d) + 0x20); /* sqc2       $vf4, 0x20($4) */
    rg_vu0_sqc2(5, (char *)(d) + 0x40); /* sqc2       $vf5, 0x40($4) */
    rg_vu0_sqc2(6, (char *)(d) + 0x60); /* sqc2       $vf6, 0x60($4) */
    rg_vu0_sqc2(7, (char *)(d) + 0x50); /* sqc2       $vf7, 0x50($4) */
    rg_vu0_sqc2(8, (char *)(d) + 0x30); /* sqc2      $vf8, 0x30($4) */
}
