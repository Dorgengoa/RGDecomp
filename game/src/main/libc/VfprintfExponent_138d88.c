#include "types.h"

asm void VfprintfExponent_138d88(void)
{
    .set noreorder;
    sb         $6, 0x0($4);
    addiu      $6, $4, 0x1;
    bgez       $5, L00138DA8;
    addiu     $29, $29, -0x140;
    addiu      $2, $0, 0x2D;
    b          L00138DAC;
    negu      $5, $5;
    nop;
  L00138DA8:
    addiu      $2, $0, 0x2B;
  L00138DAC:
    sb         $2, 0x0($6);
    addiu      $6, $4, 0x2;
    addiu      $7, $29, 0x134;
    slti       $2, $5, 0xA;
    bnez       $2, L00138E40;
    daddu     $9, $7, $0;
    addiu      $8, $0, 0xA;
    div $5, $8;
    nop;
  L00138DD0:
    addiu      $7, $7, -0x1;
    beql       $8, $0, L00138DDC;
        .word 0x000001CD;
  L00138DDC:
    mflo       $3;
    mfhi       $2;
    daddu      $5, $3, $0;
    addiu      $2, $2, 0x30;
    slti       $3, $5, 0xA;
    sb         $2, 0x0($7);
    beql       $3, $0, L00138DD0;
    div $5, $8;
    addiu      $7, $7, -0x1;
    addiu      $2, $5, 0x30;
    sltu       $3, $7, $9;
    beqz       $3, L00138E58;
    sb        $2, 0x0($7);
    daddu      $5, $9, $0;
    nop;
  L00138E18:
    lbu        $2, 0x0($7);
    addiu      $7, $7, 0x1;
    sltu       $3, $7, $5;
    sb         $2, 0x0($6);
    nop;
    bnez       $3, L00138E18;
    addiu     $6, $6, 0x1;
    b          L00138E5C;
    subu      $2, $6, $4;
    nop;
  L00138E40:
    addiu      $2, $0, 0x30;
    addiu      $3, $5, 0x30;
    sb         $2, 0x0($6);
    addiu      $6, $6, 0x1;
    sb         $3, 0x0($6);
    addiu      $6, $6, 0x1;
  L00138E58:
    subu       $2, $6, $4;
  L00138E5C:
    jr         $31;
    addiu     $29, $29, 0x140;
}

