#include "types.h"

asm void Fabsf_128e08(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    mov.s      $f0, $f12;
    swc1       $f0, 0x0($29);
    lui        $2, (0x7FFFFFFF >> 16);
    lw         $3, 0x0($29);
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    and        $3, $3, $2;
    mtc1       $3, $f0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
