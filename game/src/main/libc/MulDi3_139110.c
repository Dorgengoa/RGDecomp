#include "types.h"

asm void MulDi3_139110(void)
{
    .set noreorder;
    dsll32     $2, $5, 0;
    dsra32     $2, $2, 0;
    dsra32     $5, $5, 0;
    dsll32     $3, $4, 0;
    dsra32     $3, $3, 0;
    multu      $3, $2;
    mflo       $6;
    mfhi       $8;
    dsll32     $6, $6, 0;
    dsra32     $4, $4, 0;
    mult       $3, $3, $5;
    addiu      $5, $0, -0x1;
    dsll32     $5, $5, 0;
    mult1      $4, $4, $2;
    dsrl32     $6, $6, 0;
    and        $9, $9, $5;
    lui        $7, (0xFFFF0000 >> 16);
    dsrl32     $7, $7, 0;
    or         $9, $9, $6;
    dsll32     $8, $8, 0;
    and        $9, $9, $7;
    or         $9, $9, $8;
    addu       $3, $3, $4;
    dsra32     $2, $9, 0;
    and        $7, $9, $7;
    addu       $2, $2, $3;
    dsll32     $2, $2, 0;
    jr         $31;
    or        $2, $7, $2;
}

