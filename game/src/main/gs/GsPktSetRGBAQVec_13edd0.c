#include "types.h"

asm void GsPktSetRGBAQVec_13edd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $3, $29, 0x0;
    lqc2       $vf10, 0x0($5);
    vftoi0.xyzw $vf10, $vf10;
    sqc2       $vf10, 0x0($3);
    lw         $5, 0x4($29);
    addiu      $3, $0, 0x1;
    lw         $7, 0x8($29);
    lw         $6, 0xC($29);
    dsll       $8, $5, 8;
    lw         $9, 0x0($29);
    lwu        $5, 0x110($4);
    dsll       $7, $7, 16;
    lw         $10, 0xF4($4);
    dsll       $6, $6, 24;
    or         $8, $9, $8;
    or         $7, $7, $8;
    dsll32     $5, $5, 0;
    or         $6, $6, $7;
    or         $5, $5, $6;
    sd         $5, 0x0($10);
    sd         $3, 0x8($10);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    sw         $3, 0xF4($4);
    jr         $31;
    addiu     $29, $29, 0x10;
}

