#include "types.h"

extern void SegmentSphereIntersect_13da60(void);

asm void SegmentSphereIntersectWorld_13d9d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $4, $0;
    lwc1       $f12, 0xC($4);
    daddu      $16, $7, $0;
    addiu      $4, $29, 0x40;
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x0($17);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($4);
    addiu      $5, $29, 0x30;
    lqc2       $vf4, 0x0($6);
    lqc2       $vf5, 0x0($17);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($5);
    jal        SegmentSphereIntersect_13da60;
    daddu     $6, $16, $0;
    b          L0013DA3C;
    daddu     $4, $0, $0;
  L0013DA24:
    addu       $3, $16, $3;
    lqc2       $vf15, 0x0($3);
    lqc2       $vf16, 0x0($17);
    vadd.xyzw  $vf15, $vf15, $vf16;
    sqc2       $vf15, 0x0($3);
    addiu      $4, $4, 0x1;
  L0013DA3C:
    slt        $3, $4, $2;
    bnel       $3, $0, L0013DA24;
    sll       $3, $4, 4;
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

