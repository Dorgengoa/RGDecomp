#include "types.h"

/* Sibling of MtxTransformPointsMinMax_13c780, single running transform (no min/max pair). */

void MtxTransformPoints_13c810(void)
{
    asm volatile {
        .set noreorder
        addi  $3, $7, -0x1
        lqc2  $vf16, 0x0($6)
        lqc2  $vf10, 0x0($5)
        lqc2  $vf11, 0x10($5)
        lqc2  $vf12, 0x20($5)
        lqc2  $vf13, 0x30($5)
    L0013C828:
        vmulax.xyzw  $ACC, $vf10, $vf16x
        vmadday.xyzw $ACC, $vf11, $vf16y
        vmaddaz.xyzw $ACC, $vf12, $vf16z
        vmaddw.xyzw  $vf17, $vf13, $vf16w
        addi  $3, $3, -0x1
        addi  $4, $4, 0x10
        addi  $6, $6, 0x10
        sqc2  $vf17, -0x10($4)
        lqc2  $vf16, 0x0($6)
        bgez  $3, L0013C828
        vnop
    }
}
