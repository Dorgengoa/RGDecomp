#include "types.h"

extern void MulDi3_139110(void);

asm void Rand_133710(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $16, 0x0($29);
    lui        $5, (0x5851F42D >> 16);
    ori        $5, $5, (0x5851F42D & 0xFFFF);
    dsll       $5, $5, 16;
    ori        $5, $5, 0x4C95;
    dsll       $5, $5, 16;
    ori        $5, $5, 0x7F2D;
    lw         $16, -0x67A8($2);
    sd         $31, 0x8($29);
    jal        MulDi3_139110;
    ld        $4, 0xA8($16);
    lui        $4, (0x7FFFFFFF >> 16);
    ori        $4, $4, (0x7FFFFFFF & 0xFFFF);
    daddiu     $3, $2, 0x1;
    ld         $31, 0x8($29);
    dsrl32     $2, $3, 0;
    sd         $3, 0xA8($16);
    and        $2, $2, $4;
    ld         $16, 0x0($29);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
