#include "types.h"

asm void kFindAddress_120780(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    beq        $2, $6, L001207B4;
    sltu      $2, $4, $5;
    beql       $2, $0, L001207B8;
    movz      $4, $0, $2;
    addiu      $4, $4, 0x4;
  L00120798:
    lw         $2, 0x0($4);
    beq        $2, $6, L001207B4;
    sltu      $2, $4, $5;
    bnel       $2, $0, L00120798;
    addiu     $4, $4, 0x4;
    b          L001207B8;
    movz      $4, $0, $2;
  L001207B4:
    movz       $4, $0, $2;
  L001207B8:
    jr         $31;
    daddu     $2, $4, $0;
}
