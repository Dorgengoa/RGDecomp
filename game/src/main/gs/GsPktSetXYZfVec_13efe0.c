#include "types.h"

asm void GsPktSetXYZfVec_13efe0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $3, $29, 0x0;
    lqc2       $vf10, 0x0($5);
    vftoi4.xy  $vf10, $vf10;
    vftoi0.z   $vf10, $vf10;
    sqc2       $vf10, 0x0($3);
    lw         $8, 0x0($29);
    addiu      $3, $0, 0x5;
    lw         $5, 0x120($4);
    lw         $7, 0x4($29);
    lw         $6, 0x124($4);
    addu       $8, $8, $5;
    lw         $9, 0xF4($4);
    lw         $5, 0x8($29);
    dsll32     $8, $8, 0;
    addu       $6, $7, $6;
    dsra32     $8, $8, 0;
    dsll32     $6, $6, 0;
    dsra32     $6, $6, 0;
    dsll32     $5, $5, 0;
    dsll       $6, $6, 16;
    or         $6, $8, $6;
    or         $5, $5, $6;
    sd         $5, 0x0($9);
    sd         $3, 0x8($9);
    lw         $3, 0xF4($4);
    addiu      $3, $3, 0x10;
    sw         $3, 0xF4($4);
    jr         $31;
    addiu     $29, $29, 0x10;
}

