#include "types.h"

asm void PackD_13afa8(void)
{
    .set noreorder;
    lw         $3, 0x0($4);
    daddu      $7, $0, $0;
    ld         $5, 0x10($4);
    sltiu      $2, $3, 0x2;
    beqz       $2, L0013AFD8;
    lw        $8, 0x4($4);
    ori        $2, $0, 0x8000;
    dsll32     $2, $2, 4;
    addiu      $7, $0, 0x7FF;
    b          L0013B024;
    or        $5, $5, $2;
    nop;
  L0013AFD8:
    xori       $2, $3, 0x4;
    beql       $2, $0, L0013B018;
    addiu     $7, $0, 0x7FF;
    xori       $2, $3, 0x2;
    beql       $2, $0, L0013B024;
    daddu     $5, $0, $0;
    beqz       $5, L0013B024;
    nop;
    lw         $4, 0x8($4);
    slti       $2, $4, -0x3FE;
    bnel       $2, $0, L0013B024;
    daddu     $5, $0, $0;
    slti       $2, $4, 0x400;
    bnel       $2, $0, L0013B020;
    addiu     $7, $4, 0x3FF;
    addiu      $7, $0, 0x7FF;
  L0013B018:
    b          L0013B024;
    daddu     $5, $0, $0;
  L0013B020:
    dsrl       $5, $5, 8;
  L0013B024:
    ori        $3, $0, 0xFFF0;
    dsll32     $3, $3, 16;
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 12;
    and        $2, $5, $2;
    and        $6, $6, $3;
    or         $6, $6, $2;
    lui        $2, (0x800FFFFF >> 16);
    ori        $2, $2, (0x800FFFFF & 0xFFFF);
    dsll       $2, $2, 16;
    ori        $2, $2, 0xFFFF;
    dsll       $2, $2, 16;
    ori        $2, $2, 0xFFFF;
    andi       $3, $7, 0x7FF;
    and        $6, $6, $2;
    dsll32     $3, $3, 20;
    addiu      $4, $0, -0x1;
    dsrl       $4, $4, 1;
    or         $6, $6, $3;
    dsll32     $2, $8, 31;
    and        $6, $6, $4;
    jr         $31;
    or        $2, $6, $2;
}

