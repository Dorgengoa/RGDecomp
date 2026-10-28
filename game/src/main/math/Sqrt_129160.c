#include "types.h"

extern void IeeeSqrt_124130(void);

asm void Sqrt_129160(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    ld         $31, 0x0($29);
    j          IeeeSqrt_124130;
    addiu     $29, $29, 0x10;
}
