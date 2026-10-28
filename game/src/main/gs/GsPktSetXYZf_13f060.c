#include "types.h"

asm void GsPktSetXYZf_13f060(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $5, $29, 0x10;
    beqz       $5, L0013F08C;
    addiu     $3, $0, 0x10;
  L0013F070:
    sb         $0, 0x0($5);
    addiu      $3, $3, -0x1;
    addiu      $5, $5, 0x1;
    nop;
    nop;
    bnez       $3, L0013F070;
    nop;
  L0013F08C:
    swc1       $f12, 0x10($29);
    addiu      $5, $29, 0x10;
    swc1       $f13, 0x14($29);
    addiu      $3, $29, 0x0;
    swc1       $f14, 0x18($29);
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
    addiu     $29, $29, 0x20;
}

