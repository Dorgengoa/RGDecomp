#include "types.h"

asm void GsPktSetST_13ed10(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lw         $7, 0xF4($4);
    swc1       $f13, 0xC($29);
    addiu      $3, $0, 0x2;
    swc1       $f12, 0x8($29);
    lwu        $5, 0xC($29);
    lwu        $6, 0x8($29);
    swc1       $f14, 0x110($4);
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

