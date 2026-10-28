#include "types.h"

asm void KernelSinf_1279d8(void)
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
    ori        $2, $2, (0x31FFFFFF & 0xFFFF);
    slt        $2, $2, $3;
    bnel       $2, $0, L00127A1C;
    mul.s     $f3, $f12, $f12;
    beqz       $5, L00127AD4;
    mov.s     $f0, $f12;
    mul.s      $f3, $f12, $f12;
  L00127A1C:
    lui        $1, (0x2F2EC9D2 >> 16);
    ori        $1, $1, (0x2F2EC9D2 & 0xFFFF);
    mtc1       $1, $f0;
    lui        $1, (0xB2D72F34 >> 16);
    ori        $1, $1, (0xB2D72F34 & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f3, $f0;
    mul.s      $f4, $f3, $f12;
    add.s      $f0, $f0, $f1;
    lui        $1, (0x3638EF1A >> 16);
    ori        $1, $1, (0x3638EF1A & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f3, $f0;
    add.s      $f0, $f0, $f1;
    lui        $1, (0xB9500D01 >> 16);
    ori        $1, $1, (0xB9500D01 & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f3, $f0;
    add.s      $f0, $f0, $f1;
    lui        $1, (0x3C088889 >> 16);
    ori        $1, $1, (0x3C088889 & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f3, $f0;
    bnez       $4, L00127AA0;
    add.s     $f1, $f0, $f1;
    mul.s      $f0, $f3, $f1;
    lui        $1, (0xBE2AAAAA >> 16);
    ori        $1, $1, (0xBE2AAAAA & 0xFFFF);
    mtc1       $1, $f1;
    add.s      $f0, $f0, $f1;
    mul.s      $f0, $f4, $f0;
    b          L00127AD4;
    add.s     $f0, $f12, $f0;
  L00127AA0:
    lui        $1, (0x3F000000 >> 16);
    mtc1       $1, $f0;
    mul.s      $f2, $f4, $f1;
    lui        $1, (0xBE2AAAAA >> 16);
    ori        $1, $1, (0xBE2AAAAA & 0xFFFF);
    mtc1       $1, $f1;
    mul.s      $f0, $f13, $f0;
    mul.s      $f1, $f4, $f1;
    sub.s      $f0, $f0, $f2;
    mul.s      $f0, $f3, $f0;
    sub.s      $f0, $f0, $f13;
    sub.s      $f0, $f0, $f1;
    sub.s      $f0, $f12, $f0;
  L00127AD4:
    jr         $31;
    addiu     $29, $29, 0x10;
}
