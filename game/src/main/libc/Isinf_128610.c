#include "types.h"

asm void Isinf_128610(void)
{
    .set noreorder;
    dsll32     $3, $4, 0;
    dsra32     $3, $3, 0;
    dsra32     $4, $4, 0;
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $6, (0x7FF00000 >> 16);
    negu       $5, $3;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    or         $3, $3, $5;
    and        $4, $4, $2;
    srl        $3, $3, 31;
    addiu      $2, $0, 0x1;
    or         $4, $4, $3;
    subu       $4, $6, $4;
    negu       $3, $4;
    or         $4, $4, $3;
    srl        $4, $4, 31;
    jr         $31;
    subu      $2, $2, $4;
}
