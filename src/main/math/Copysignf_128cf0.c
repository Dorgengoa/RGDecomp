#include "types.h"

asm void Copysignf_128cf0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    mov.s      $f0, $f12;
    swc1       $f0, 0x0($29);
    swc1       $f13, 0x4($29);
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $3, (0x80000000 >> 16);
    lw         $4, 0x4($29);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    and        $3, $4, $3;
    lw         $4, 0x0($29);
    and        $2, $4, $2;
    or         $2, $2, $3;
    mtc1       $2, $f0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
