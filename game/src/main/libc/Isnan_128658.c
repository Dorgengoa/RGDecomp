#include "types.h"

asm void Isnan_128658(void)
{
    .set noreorder;
    daddu      $2, $4, $0;
    dsll32     $4, $2, 0;
    dsra32     $4, $4, 0;
    dsra32     $2, $2, 0;
    lui        $3, (0x7FFFFFFF >> 16);
    lui        $6, (0x7FF00000 >> 16);
    negu       $5, $4;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    or         $4, $4, $5;
    and        $2, $2, $3;
    srl        $4, $4, 31;
    or         $2, $2, $4;
    subu       $2, $6, $2;
    jr         $31;
    srl       $2, $2, 31;
}
