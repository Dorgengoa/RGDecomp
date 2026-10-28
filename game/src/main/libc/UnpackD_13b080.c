#include "types.h"

asm void UnpackD_13b080(void)
{
    .set noreorder;
    ld         $2, 0x0($4);
    daddu      $6, $5, $0;
    addiu      $5, $0, -0x1;
    dsrl       $5, $5, 12;
    dsrl32     $3, $2, 20;
    dsrl32     $4, $2, 31;
    andi       $7, $3, 0x7FF;
    and        $3, $2, $5;
    bnez       $7, L0013B0B8;
    sw        $4, 0x4($6);
    addiu      $2, $0, 0x2;
    jr         $31;
    sw        $2, 0x0($6);
    nop;
  L0013B0B8:
    addiu      $2, $0, 0x7FF;
    bnel       $7, $2, L0013B118;
    dsll      $3, $3, 8;
    addiu      $2, $0, 0x3FF;
    bnez       $3, L0013B0E8;
    sw        $2, 0x8($6);
    addiu      $3, $0, 0x4;
    ori        $2, $0, 0x8000;
    dsll32     $2, $2, 13;
    sd         $2, 0x10($6);
    jr         $31;
    sw        $3, 0x0($6);
  L0013B0E8:
    ori        $2, $0, 0x8000;
    dsll32     $2, $2, 4;
    and        $2, $3, $2;
    beqz       $2, L0013B108;
    addiu     $2, $0, 0x1;
    b          L0013B10C;
    sw        $2, 0x0($6);
    nop;
  L0013B108:
    sw         $0, 0x0($6);
  L0013B10C:
    jr         $31;
    sd        $3, 0x10($6);
    nop;
  L0013B118:
    ori        $2, $0, 0x8000;
    dsll32     $2, $2, 13;
    or         $3, $3, $2;
    addiu      $2, $0, 0x3;
    addiu      $4, $7, -0x3FF;
    sd         $3, 0x10($6);
    sw         $4, 0x8($6);
    jr         $31;
    sw        $2, 0x0($6);
}

