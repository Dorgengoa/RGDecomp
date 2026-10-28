#include "types.h"

asm void KernelCosf_127020(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    mov.s      $f0, $f12;
    swc1       $f0, 0x0($29);
    lui        $3, (0x7FFFFFFF >> 16);
    lw         $6, 0x0($29);
    .word      0x46006024;
    mfc1       $5, $f0;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    lui        $2, (0x31FFFFFF >> 16);
    and        $3, $6, $3;
    lui        $4, (0x3E999999 >> 16);
    ori        $2, $2, (0x31FFFFFF & 0xFFFF);
    ori        $4, $4, (0x3E999999 & 0xFFFF);
    slt        $2, $2, $3;
    bnez       $2, L00127070;
    slt       $4, $4, $3;
    lui        $1, (0x3F800000 >> 16);
    mtc1       $1, $f0;
    beqz       $5, L00127168;
    nop;
  L00127070:
    mul.s      $f4, $f12, $f12;
    lui        $1, (0xAD47D74E >> 16);
    ori        $1, $1, (0xAD47D74E & 0xFFFF);
    mtc1       $1, $f0;
    lui        $1, (0x310F74F5 >> 16);
    ori        $1, $1, (0x310F74F5 & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f4, $f0;
    add.s      $f0, $f0, $f1;
    lui        $1, (0xB493F27B >> 16);
    ori        $1, $1, (0xB493F27B & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f4, $f0;
    add.s      $f0, $f0, $f1;
    lui        $1, (0x37D00D00 >> 16);
    ori        $1, $1, (0x37D00D00 & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f4, $f0;
    add.s      $f0, $f0, $f1;
    lui        $1, (0xBAB60B60 >> 16);
    ori        $1, $1, (0xBAB60B60 & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f4, $f0;
    add.s      $f0, $f0, $f1;
    lui        $1, (0x3D2AAAAA >> 16);
    ori        $1, $1, (0x3D2AAAAA & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f4, $f0;
    add.s      $f0, $f0, $f1;
    bnez       $4, L00127118;
    mul.s     $f1, $f4, $f0;
    mul.s      $f1, $f4, $f1;
    lui        $1, (0x3F000000 >> 16);
    mtc1       $1, $f0;
    mul.s      $f2, $f12, $f13;
    lui        $1, (0x3F800000 >> 16);
    mtc1       $1, $f3;
    mul.s      $f0, $f4, $f0;
    sub.s      $f1, $f1, $f2;
    sub.s      $f0, $f0, $f1;
    b          L00127168;
    sub.s     $f0, $f3, $f0;
  L00127118:
    lui        $2, (0x3F480000 >> 16);
    lui        $1, (0x3E900000 >> 16);
    mtc1       $1, $f5;
    slt        $2, $2, $3;
    bnez       $2, L00127138;
    lui       $2, (0xFF000000 >> 16);
    addu       $3, $3, $2;
    mtc1       $3, $f5;
  L00127138:
    lui        $1, (0x3F000000 >> 16);
    mtc1       $1, $f0;
    mul.s      $f2, $f4, $f1;
    mul.s      $f3, $f12, $f13;
    lui        $1, (0x3F800000 >> 16);
    mtc1       $1, $f1;
    mul.s      $f0, $f4, $f0;
    sub.s      $f1, $f1, $f5;
    sub.s      $f2, $f2, $f3;
    sub.s      $f0, $f0, $f5;
    sub.s      $f0, $f0, $f2;
    sub.s      $f0, $f1, $f0;
  L00127168:
    jr         $31;
    addiu     $29, $29, 0x10;
}
