#include "types.h"

extern void VecNormalize_13bd90(void);

asm void VecSetLength_13e000(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x20($29);
    sq         $16, 0x10($29);
    swc1       $f20, 0x0($29);
    daddu      $16, $4, $0;
    mov.s      $f20, $f12;
    jal        VecNormalize_13bd90;
    addiu     $4, $29, 0x30;
    addiu      $3, $29, 0x30;
    lqc2       $vf4, 0x0($3);
    mfc1       $8, $f20;
    nop;
    qmtc2.ni   $8, $vf5;
    vmulx.xyzw $vf6, $vf4, $vf5x;
    sqc2       $vf6, 0x0($16);
    ld         $31, 0x20($29);
    lwc1       $f20, 0x0($29);
    lq         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

