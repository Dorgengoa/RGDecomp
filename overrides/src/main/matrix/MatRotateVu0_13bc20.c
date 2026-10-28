/* rg-override: replaces game/src/main/matrix/MatRotateVu0_13bc20.c sha256 ee7c4187a31ec78dc9904a45e2ad025c5b393f4742a13e4b709bddc56091bf91
 * why: asm body (asmexclude); C port on the VU0 model, `vcallms 0x0` runs the retail VU0
 * microprogram (uploaded by GfxSysInit) on the shared register file (src/ps2/vu0_micro.c);
 * RG_VU0_LOCAL (RG_VU0_MODE local/native): the program as native C instead */
#include "types.h"

/* m = m * R(*rot): the microprogram builds R from the Euler angles in vf2
   with unit scale (vf1.xyz = 1) and zero translation (vf3 = 0); each row of m
   is then multiplied through vf4..vf7 in place. */
#if RG_VU0_IS_LOCAL
/* native: R from the microprogram as C (src/sce/vu0/vu0_srt.c), then the
   listing's row products in the same operation order (docs/NATIVE-CPU.md) */
void MatRotateVu0_13bc20(void *m, void *rot)
{ RG_VU0_FRAME;
    rg_vf one, zero, vr, R[4], row[4], out[4];
    int i, k;
    __builtin_memcpy(&vr, rot, 16);                   /* lqc2 $vf2, 0x0($5) */
    for (k = 0; k < 4; k++) {
        one.u[k] = rg_vu_addf(0, 0x3F800000u);        /* vaddw.xyz $vf1, $vf0, $vf0w */
        zero.u[k] = rg_vu_mulf(k == 3 ? 0x3F800000u : 0, 0); /* vmulx.xyzw $vf3, $vf0, $vf0x */
    }
    rg_vu0_srt(R, &one, &vr, &zero);                  /* vcallms 0x0; vnop */
    __builtin_memcpy(row, m, 64);                     /* lqc2 $vf10..$vf13 */
    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++) {
            rg_vu_u32 acc = rg_vu_mulf(R[0].u[k], row[i].u[0]);         /* vmulax  ACC, vf4, rowx */
            acc = rg_vu_addf(acc, rg_vu_mulf(R[1].u[k], row[i].u[1]));  /* vmadday ACC, vf5, rowy */
            if (i < 3) {
                out[i].u[k] = rg_vu_addf(acc, rg_vu_mulf(R[2].u[k], row[i].u[2])); /* vmaddz */
            } else {
                acc = rg_vu_addf(acc, rg_vu_mulf(R[2].u[k], row[i].u[2]));         /* vmaddaz */
                out[i].u[k] = rg_vu_addf(acc, rg_vu_mulf(R[3].u[k], row[i].u[3])); /* vmaddw */
            }
        }
    __builtin_memcpy(m, out, 64);                     /* sqc2 $vf20..$vf23 */
}
#else
void MatRotateVu0_13bc20(void *m, void *rot)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(2, (char *)rot); /* lqc2       $vf2, 0x0($5) */
    rg_vu0_fmac(RG_VADD, RG_XYZ, 1, 0, 0, RG_BC_W); /* vaddw.xyz  $vf1, $vf0, $vf0w */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 3, 0, 0, RG_BC_X); /* vmulx.xyzw $vf3, $vf0, $vf0x */
    rg_vu0_vcallms(0x0);         /* vcallms    0x0 */
    rg_vu0_waitq();              /* vnop (waits for the program on hardware) */
    rg_vu0_lqc2(10, (char *)m); /* lqc2       $vf10, 0x0($4) */
    rg_vu0_lqc2(11, (char *)m + 0x10); /* lqc2       $vf11, 0x10($4) */
    rg_vu0_lqc2(12, (char *)m + 0x20); /* lqc2       $vf12, 0x20($4) */
    rg_vu0_lqc2(13, (char *)m + 0x30); /* lqc2       $vf13, 0x30($4) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 10, RG_BC_X); /* vmulax.xyzw $ACC, $vf4, $vf10x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 10, RG_BC_Y); /* vmadday.xyzw $ACC, $vf5, $vf10y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 20, 6, 10, RG_BC_Z); /* vmaddz.xyzw $vf20, $vf6, $vf10z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 11, RG_BC_X); /* vmulax.xyzw $ACC, $vf4, $vf11x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 11, RG_BC_Y); /* vmadday.xyzw $ACC, $vf5, $vf11y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 21, 6, 11, RG_BC_Z); /* vmaddz.xyzw $vf21, $vf6, $vf11z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 12, RG_BC_X); /* vmulax.xyzw $ACC, $vf4, $vf12x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 12, RG_BC_Y); /* vmadday.xyzw $ACC, $vf5, $vf12y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 22, 6, 12, RG_BC_Z); /* vmaddz.xyzw $vf22, $vf6, $vf12z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 13, RG_BC_X); /* vmulax.xyzw $ACC, $vf4, $vf13x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 13, RG_BC_Y); /* vmadday.xyzw $ACC, $vf5, $vf13y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 6, 13, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf6, $vf13z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 23, 7, 13, RG_BC_W); /* vmaddw.xyzw $vf23, $vf7, $vf13w */
    rg_vu0_sqc2(20, (char *)m); /* sqc2       $vf20, 0x0($4) */
    rg_vu0_sqc2(21, (char *)m + 0x10); /* sqc2       $vf21, 0x10($4) */
    rg_vu0_sqc2(22, (char *)m + 0x20); /* sqc2       $vf22, 0x20($4) */
    rg_vu0_sqc2(23, (char *)m + 0x30); /* sqc2      $vf23, 0x30($4) */
}
#endif
