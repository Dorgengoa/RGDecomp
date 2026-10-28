#include "types.h"

asm void Ulp_1327d8(void)
{
    .set noreorder;
    lui        $2, (0x7FF00000 >> 16);
    dsra32     $4, $4, 0;
    and        $4, $4, $2;
    lui        $3, (0xFCC00000 >> 16);
    addu       $4, $4, $3;
    negu       $2, $4;
    blez       $4, L00132818;
    dsll32    $6, $4, 0;
    lui        $2, (0xFFFF0000 >> 16);
    dsrl32     $2, $2, 0;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    and        $5, $5, $2;
    or         $5, $5, $6;
    b          L0013289C;
    and       $5, $5, $3;
  L00132818:
    sra        $4, $2, 20;
    slti       $2, $4, 0x14;
    beql       $2, $0, L00132858;
    addiu     $4, $4, -0x14;
    lui        $2, (0x80000 >> 16);
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    srav       $2, $2, $4;
    and        $5, $5, $3;
    dsll32     $2, $2, 0;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    or         $5, $5, $2;
    b          L0013289C;
    and       $5, $5, $3;
    nop;
  L00132858:
    lui        $3, (0xFFFF0000 >> 16);
    dsrl32     $3, $3, 0;
    slti       $2, $4, 0x1F;
    nor        $6, $0, $4;
    beqz       $2, L00132880;
    and       $5, $5, $3;
    addiu      $2, $0, 0x1;
    b          L00132884;
    sllv      $2, $2, $6;
    nop;
  L00132880:
    addiu      $2, $0, 0x1;
  L00132884:
    dsll32     $2, $2, 0;
    addiu      $3, $0, -0x1;
    dsll32     $3, $3, 0;
    dsrl32     $2, $2, 0;
    and        $5, $5, $3;
    or         $5, $5, $2;
  L0013289C:
    daddu      $2, $5, $0;
    jr         $31;
    nop;
}
