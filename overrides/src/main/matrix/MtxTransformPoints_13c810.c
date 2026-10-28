/* rg-override: replaces game/src/main/matrix/MtxTransformPoints_13c810.c sha256 03b025f4134f896cde6a4f12da4719119e70d6d72e597c82ea55dd2f25ef0203
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* d[i] = m * s[i] (full 4x4, w included) for n points.  The loop counter is
   tested after the decrement (bgez), so n <= 0 still transforms one point, and
   the software-pipelined lqc2 reads one qword past the last source point. */
void MtxTransformPoints_13c810(void *d, const void *m, const void *s, s32 n)
{ RG_VU0_FRAME;
    s32 k = n - 1;                                                  /* addi $3, $7, -1 */
    char *dp = (char *)d;
    const char *sp = (const char *)s;
    rg_vu0_lqc2(16, sp);                                            /* lqc2 vf16, 0($6) */
    rg_vu0_lqc2(10, (const char *)m);                               /* lqc2 vf10, 0($5) */
    rg_vu0_lqc2(11, (const char *)m + 0x10);                        /* lqc2 vf11, 0x10($5) */
    rg_vu0_lqc2(12, (const char *)m + 0x20);                        /* lqc2 vf12, 0x20($5) */
    rg_vu0_lqc2(13, (const char *)m + 0x30);                        /* lqc2 vf13, 0x30($5) */
    do {
        rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 10, 16, RG_BC_X);         /* vmulax.xyzw ACC, vf10, vf16x */
        rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 16, RG_BC_Y);        /* vmadday.xyzw ACC, vf11, vf16y */
        rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 12, 16, RG_BC_Z);        /* vmaddaz.xyzw ACC, vf12, vf16z */
        rg_vu0_fmac(RG_VMADD, RG_XYZW, 17, 13, 16, RG_BC_W);        /* vmaddw.xyzw vf17, vf13, vf16w */
        k = k - 1;                                                  /* addi $3, $3, -1 */
        dp += 0x10;                                                 /* addi $4, $4, 0x10 */
        sp += 0x10;                                                 /* addi $6, $6, 0x10 */
        rg_vu0_sqc2(17, dp - 0x10);                                 /* sqc2 vf17, -0x10($4) */
        rg_vu0_lqc2(16, sp);                                        /* lqc2 vf16, 0($6) */
    } while (k >= 0);                                               /* bgez $3, loop; vnop */
}
