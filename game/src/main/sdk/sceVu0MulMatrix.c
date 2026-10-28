#include "types.h"

/* Hand-written VU0 4x4 matrix * (array of vectors) loop. Retail ends with
   an explicit jr $31/nop pair AND a further dead standalone nop -- try
   writing the whole tail verbatim first (this differs from the leaf-stub
   case because of the internal loop branch). */

void sceVu0MulMatrix(void)
{
    asm volatile {
        .set noreorder
        lqc2  $vf4, 0x0($5)
        lqc2  $vf5, 0x10($5)
        lqc2  $vf6, 0x20($5)
        lqc2  $vf7, 0x30($5)
        addiu $7, $0, 0x4
    L0010A904:
        lqc2  $vf8, 0x0($6)
        vmulax.xyzw  $ACC, $vf4, $vf8x
        vmadday.xyzw $ACC, $vf5, $vf8y
        vmaddaz.xyzw $ACC, $vf6, $vf8z
        vmaddw.xyzw  $vf9, $vf7, $vf8w
        sqc2  $vf9, 0x0($4)
        addi  $7, $7, -0x1
        addi  $6, $6, 0x10
        bne   $0, $7, L0010A904
        addi  $4, $4, 0x10
    }
}
