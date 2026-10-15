#include "types.h"

asm void ftoi(void)
{
    .set noreorder;
    daddu      $5, $4, $0;
    dsll       $2, $5, 1;
    dsrl32     $6, $2, 21;
    daddiu     $6, $6, -0x433;
    slti       $2, $6, -0x35;
    beqz       $2, L00118144;
    slti      $2, $6, 0xD;
    jr         $31;
    daddu     $2, $0, $0;
  L00118144:
    bnez       $2, L00118154;
    dsll      $2, $5, 12;
    jr         $31;
    addiu     $2, $0, 0x270F;
  L00118154:
    ori        $3, $0, 0x8000;
    dsll32     $3, $3, 5;
    dsrl       $5, $2, 12;
    bgez       $6, L00118198;
    or        $5, $5, $3;
    dsubu      $6, $0, $6;
    addiu      $2, $0, 0x3;
    daddiu     $3, $6, -0x2;
    dsll32     $3, $3, 0;
    dsra32     $3, $3, 0;
    dsrlv      $5, $5, $3;
    andi       $4, $5, 0x3;
    bnel       $4, $2, L001181A4;
    dsrl      $5, $5, 2;
    dsrl       $2, $5, 2;
    b          L001181A4;
    daddiu    $5, $2, 0x1;
  L00118198:
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    dsllv      $5, $5, $2;
  L001181A4:
    dsll32     $2, $5, 0;
    jr         $31;
    dsra32    $2, $2, 0;
}
