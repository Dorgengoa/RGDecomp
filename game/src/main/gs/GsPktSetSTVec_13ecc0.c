#include "types.h"

asm void GsPktSetSTVec_13ecc0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lw         $7, 0xF4($4);
    lwc1       $f1, 0x4($5);
    addiu      $3, $0, 0x2;
    lwc1       $f0, 0x0($5);
    lwc1       $f2, 0x8($5);
    swc1       $f1, 0x8($29);
    swc1       $f0, 0xC($29);
    lwu        $5, 0x8($29);
    swc1       $f2, 0x110($4);
    lwu        $6, 0xC($29);
    dsll32     $5, $5, 0;
    or         $5, $6, $5;
    sd         $5, 0x0($7);
    sd         $3, 0x8($7);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    sw         $3, 0xF4($4);
    jr         $31;
    addiu     $29, $29, 0x10;
}

