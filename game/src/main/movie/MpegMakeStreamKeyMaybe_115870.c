#include "types.h"

asm void MpegMakeStreamKeyMaybe_115870(void)
{
    .set noreorder;
    daddu      $7, $5, $0;
    daddu      $3, $0, $0;
    sltiu      $2, $4, 0xA;
    beqz       $2, L0011590C;
    daddu     $5, $0, $0;
    lui        $8, 0x44;
    sll        $6, $4, 4;
    addiu      $2, $8, 0x60C0;
    ori        $4, $0, 0xFFFF;
    dsll       $4, $4, 24;
    addu       $2, $2, $6;
    ld         $3, 0x8($2);
    beq        $3, $4, L001158E0;
    sltu      $2, $4, $3;
    bnez       $2, L001158C8;
    nop;
    ori        $2, $0, 0xFF00;
    dsll       $2, $2, 24;
    beq        $3, $2, L001158E8;
    daddu     $2, $0, $0;
    b          L00115910;
    nop;
  L001158C8:
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 24;
    bne        $3, $2, L001158F0;
    addiu     $2, $8, 0x60C0;
    b          L00115900;
    dsllv     $4, $7, $5;
  L001158E0:
    b          L001158F8;
    addiu     $5, $0, 0x18;
  L001158E8:
    b          L001158F8;
    addiu     $5, $0, 0x20;
  L001158F0:
    jr         $31;
    daddu     $2, $0, $0;
  L001158F8:
    addiu      $2, $8, 0x60C0;
    dsllv      $4, $7, $5;
  L00115900:
    addu       $2, $6, $2;
    ld         $3, 0x0($2);
    or         $3, $3, $4;
  L0011590C:
    daddu      $2, $3, $0;
  L00115910:
    jr         $31;
    nop;
}
