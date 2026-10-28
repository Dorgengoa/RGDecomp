/* rg-override: replaces game/src/main/matrix/MtxTransformPointsMinMax_13c780.c sha256 8c786a61aad9855beaa5a1d9c88da561b31b20d1815b9e93fc085a871f7983e1
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* d[i] = m * s[i] for n points (n >= 2 as the loop is laid out: the first
   point is peeled and the loop runs at least once), writing the running
   per-lane max to *mx and min to *mn.  The pipelined lqc2 reads one qword
   past the last source point. */
void MtxTransformPointsMinMax_13c780(void *d, const void *m, const void *s, s32 n,
                                     void *mx, void *mn)
{ RG_VU0_FRAME;
    s32 k = n - 1;                                                  /* addi $3, $7, -1 */
    char *dp;
    const char *sp;
    rg_vu0_lqc2(16, s);                                             /* lqc2 vf16, 0($6) */
    rg_vu0_lqc2(10, (const char *)m);                               /* lqc2 vf10, 0($5) */
    rg_vu0_lqc2(11, (const char *)m + 0x10);                        /* lqc2 vf11, 0x10($5) */
    rg_vu0_lqc2(12, (const char *)m + 0x20);                        /* lqc2 vf12, 0x20($5) */
    rg_vu0_lqc2(13, (const char *)m + 0x30);                        /* lqc2 vf13, 0x30($5) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 10, 16, RG_BC_X);             /* vmulax.xyzw ACC, vf10, vf16x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 16, RG_BC_Y);            /* vmadday.xyzw ACC, vf11, vf16y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 12, 16, RG_BC_Z);            /* vmaddaz.xyzw ACC, vf12, vf16z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 17, 13, 16, RG_BC_W);            /* vmaddw.xyzw vf17, vf13, vf16w */
    k = k - 1;                                                      /* addi $3, $3, -1 */
    dp = (char *)d + 0x10;                                          /* addi $5, $4, 0x10 */
    sp = (const char *)s + 0x10;                                    /* addi $4, $6, 0x10 */
    rg_vu0_sqc2(17, dp - 0x10);                                     /* sqc2 vf17, -0x10($5) */
    rg_vu0_lqc2(16, sp);                                            /* lqc2 vf16, 0($4) */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 20, 17, 0, RG_BC_X);              /* vaddx.xyzw vf20, vf17, vf0x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 21, 17, 0, RG_BC_X);              /* vaddx.xyzw vf21, vf17, vf0x */
    do {
        rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 10, 16, RG_BC_X);         /* vmulax.xyzw ACC, vf10, vf16x */
        rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 16, RG_BC_Y);        /* vmadday.xyzw ACC, vf11, vf16y */
        rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 12, 16, RG_BC_Z);        /* vmaddaz.xyzw ACC, vf12, vf16z */
        rg_vu0_fmac(RG_VMADD, RG_XYZW, 17, 13, 16, RG_BC_W);        /* vmaddw.xyzw vf17, vf13, vf16w */
        k = k - 1;                                                  /* addi $3, $3, -1 */
        dp += 0x10;                                                 /* addi $5, $5, 0x10 */
        sp += 0x10;                                                 /* addi $4, $4, 0x10 */
        rg_vu0_sqc2(17, dp - 0x10);                                 /* sqc2 vf17, -0x10($5) */
        rg_vu0_lqc2(16, sp);                                        /* lqc2 vf16, 0($4) */
        rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 17, RG_BC_NONE);      /* vmax.xyzw vf20, vf20, vf17 */
        rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 21, 17, RG_BC_NONE);     /* (bgez delay) vmini.xyzw vf21, vf21, vf17 */
    } while (k >= 0);                                               /* bgez $3, loop */
    rg_vu0_sqc2(20, mx);                                            /* sqc2 vf20, 0($8) */
    rg_vu0_sqc2(21, mn);                                            /* sqc2 vf21, 0($9) */
}
