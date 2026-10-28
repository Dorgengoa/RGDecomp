#include "types.h"

asm void MpegDualPrimeVectorsMaybe_10b610(void)
{
    .set noreorder;
    lw         $3, 0x184($4);
    addiu      $2, $0, 0x3;
    bne        $3, $2, L0010B730;
    nop;
    lw         $2, 0x188($4);
    beql       $2, $0, L0010B6B8;
    sll       $2, $7, 1;
    blez       $7, L0010B640;
    lw        $3, 0x0($6);
    addiu      $2, $7, 0x1;
    b          L0010B644;
    sra       $2, $2, 1;
  L0010B640:
    sra        $2, $7, 1;
  L0010B644:
    addu       $2, $2, $3;
    sw         $2, 0x0($5);
    blez       $8, L0010B660;
    lw        $3, 0x4($6);
    addiu      $2, $8, 0x1;
    b          L0010B664;
    sra       $2, $2, 1;
  L0010B660:
    sra        $2, $8, 1;
  L0010B664:
    addu       $2, $2, $3;
    addiu      $2, $2, -0x1;
    sw         $2, 0x4($5);
    sll        $2, $7, 1;
    addu       $2, $2, $7;
    blez       $7, L0010B684;
    lw        $3, 0x0($6);
    addiu      $2, $2, 0x1;
  L0010B684:
    sra        $2, $2, 1;
    addu       $2, $2, $3;
    sw         $2, 0x8($5);
    sll        $2, $8, 1;
    addu       $2, $2, $8;
    blez       $8, L0010B6A4;
    lw        $6, 0x4($6);
    addiu      $2, $2, 0x1;
  L0010B6A4:
    sra        $2, $2, 1;
  L0010B6A8:
    addu       $2, $2, $6;
    addiu      $2, $2, 0x1;
    jr         $31;
    sw        $2, 0xC($5);
  L0010B6B8:
    lw         $3, 0x0($6);
    blez       $7, L0010B6C8;
    addu      $2, $2, $7;
    addiu      $2, $2, 0x1;
  L0010B6C8:
    sra        $2, $2, 1;
    addu       $2, $2, $3;
    sw         $2, 0x0($5);
    sll        $2, $8, 1;
    addu       $2, $2, $8;
    blez       $8, L0010B6E8;
    lw        $3, 0x4($6);
    addiu      $2, $2, 0x1;
  L0010B6E8:
    sra        $2, $2, 1;
    addu       $2, $2, $3;
    addiu      $2, $2, -0x1;
    sw         $2, 0x4($5);
    blez       $7, L0010B70C;
    lw        $3, 0x0($6);
    addiu      $2, $7, 0x1;
    b          L0010B710;
    sra       $2, $2, 1;
  L0010B70C:
    sra        $2, $7, 1;
  L0010B710:
    addu       $2, $2, $3;
    sw         $2, 0x8($5);
    blez       $8, L0010B728;
    lw        $6, 0x4($6);
    b          L0010B6A4;
    addiu     $2, $8, 0x1;
  L0010B728:
    b          L0010B6A8;
    sra       $2, $8, 1;
  L0010B730:
    blez       $7, L0010B744;
    lw        $3, 0x0($6);
    addiu      $2, $7, 0x1;
    b          L0010B748;
    sra       $2, $2, 1;
  L0010B744:
    sra        $2, $7, 1;
  L0010B748:
    addu       $2, $2, $3;
    sw         $2, 0x0($5);
    blez       $8, L0010B764;
    lw        $6, 0x4($6);
    addiu      $2, $8, 0x1;
    b          L0010B768;
    sra       $2, $2, 1;
  L0010B764:
    sra        $2, $8, 1;
  L0010B768:
    addu       $6, $2, $6;
    sw         $6, 0x4($5);
    addiu      $3, $0, 0x1;
    lw         $2, 0x184($4);
    bne        $2, $3, L0010B78C;
    addiu     $2, $6, 0x1;
    addiu      $2, $6, -0x1;
    jr         $31;
    sw        $2, 0x4($5);
  L0010B78C:
    jr         $31;
    sw        $2, 0x4($5);
}

