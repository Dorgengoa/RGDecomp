#include "types.h"

/* Hand-written VU0 min/max-transform loop over an array, writing the
   running min and max vectors out at the end. Final `jr $31` is the
   TRUE end of the function (word 32 of 33, matches registered size
   0x84 exactly) -- omit it and its delay slot per lever 1, trusting the
   scheduler to slide the true last instruction (`sqc2 vf21,...`) into
   the auto jr's delay slot. */

void MtxTransformPointsMinMax_13c780(void)
{
    asm volatile {
        .set noreorder
        addi  $3, $7, -0x1
        lqc2  $vf16, 0x0($6)
        lqc2  $vf10, 0x0($5)
        lqc2  $vf11, 0x10($5)
        lqc2  $vf12, 0x20($5)
        lqc2  $vf13, 0x30($5)
        vmulax.xyzw  $ACC, $vf10, $vf16x
        vmadday.xyzw $ACC, $vf11, $vf16y
        vmaddaz.xyzw $ACC, $vf12, $vf16z
        vmaddw.xyzw  $vf17, $vf13, $vf16w
        addi  $3, $3, -0x1
        addi  $5, $4, 0x10
        addi  $4, $6, 0x10
        sqc2  $vf17, -0x10($5)
        lqc2  $vf16, 0x0($4)
        vaddx.xyzw $vf20, $vf17, $vf0x
        vaddx.xyzw $vf21, $vf17, $vf0x
    L0013C7C4:
        vmulax.xyzw  $ACC, $vf10, $vf16x
        vmadday.xyzw $ACC, $vf11, $vf16y
        vmaddaz.xyzw $ACC, $vf12, $vf16z
        vmaddw.xyzw  $vf17, $vf13, $vf16w
        addi  $3, $3, -0x1
        addi  $5, $5, 0x10
        addi  $4, $4, 0x10
        sqc2  $vf17, -0x10($5)
        lqc2  $vf16, 0x0($4)
        vmax.xyzw  $vf20, $vf20, $vf17
        bgez  $3, L0013C7C4
        vmini.xyzw $vf21, $vf21, $vf17
        nop
        sqc2  $vf20, 0x0($8)
        sqc2  $vf21, 0x0($9)
    }
}
