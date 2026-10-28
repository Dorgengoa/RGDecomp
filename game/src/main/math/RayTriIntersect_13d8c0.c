#include "types.h"

extern void PointInTriangle_13d720(void);

asm void RayTriIntersect_13d8c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    daddu      $11, $8, $0;
    sd         $31, 0x0($29);
    addiu      $8, $29, 0x40;
    lqc2       $vf4, 0x0($5);
    lqc2       $vf5, 0x0($4);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($8);
    addiu      $3, $29, 0x30;
    lqc2       $vf4, 0x0($6);
    lqc2       $vf5, 0x0($4);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($3);
    addiu      $2, $29, 0x20;
    lqc2       $vf4, 0x0($7);
    lqc2       $vf5, 0x0($4);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($2);
    addiu      $2, $29, 0x10;
    lqc2       $vf4, 0x0($11);
    lqc2       $vf5, 0x0($4);
    vsub.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($2);
    lqc2       $vf4, 0x0($9);
    lqc2       $vf5, 0x0($3);
    vmul.xyz   $vf5, $vf4, $vf5;
    vaddy.x    $vf5, $vf5, $vf5y;
    vaddz.x    $vf5, $vf5, $vf5z;
    qmfc2.ni   $2, $vf5;
    mtc1       $2, $f0;
    nop;
    neg.s      $f1, $f0;
    lqc2       $vf4, 0x0($9);
    lqc2       $vf5, 0x0($8);
    vmul.xyz   $vf5, $vf4, $vf5;
    vaddy.x    $vf5, $vf5, $vf5y;
    vaddz.x    $vf5, $vf5, $vf5z;
    qmfc2.ni   $2, $vf5;
    mtc1       $2, $f2;
    mtc1       $0, $f0;
    nop;
    c.eq.s     $f0, $f2;
    bc1fl      L0013D978;
    neg.s     $f0, $f1;
    b          L0013D9C0;
    daddu     $2, $0, $0;
  L0013D978:
    nop;
    div.s      $f0, $f0, $f2;
    lqc2       $vf4, 0x0($8);
    mfc1       $8, $f0;
    nop;
    qmtc2.ni   $8, $vf5;
    vmulx.xyzw $vf6, $vf4, $vf5x;
    sqc2       $vf6, 0x0($10);
    lqc2       $vf4, 0x0($10);
    lqc2       $vf5, 0x0($4);
    vadd.xyzw  $vf6, $vf4, $vf5;
    sqc2       $vf6, 0x0($10);
    daddu      $5, $6, $0;
    daddu      $6, $7, $0;
    daddu      $4, $10, $0;
    daddu      $8, $9, $0;
    jal        PointInTriangle_13d720;
    daddu     $7, $11, $0;
  L0013D9C0:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

