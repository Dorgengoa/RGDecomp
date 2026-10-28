#include "types.h"

asm void Mcmp_1325e0(void)
{
    .set noreorder;
    lw         $2, 0x10($4);
    lw         $3, 0x10($5);
    subu       $2, $2, $3;
    bnez       $2, L00132640;
    nop;
    sll        $3, $3, 2;
    addiu      $10, $4, 0x14;
    addiu      $2, $5, 0x14;
    addu       $7, $10, $3;
    addu       $9, $2, $3;
    addiu      $7, $7, -0x4;
    nop;
  L00132610:
    addiu      $9, $9, -0x4;
    lw         $5, 0x0($7);
    addiu      $6, $0, 0x1;
    lw         $4, 0x0($9);
    addiu      $2, $0, -0x1;
    sltu       $8, $10, $7;
    sltu       $3, $5, $4;
    bne        $5, $4, L00132640;
    movz      $2, $6, $3;
    bnel       $8, $0, L00132610;
    addiu     $7, $7, -0x4;
    daddu      $2, $0, $0;
  L00132640:
    jr         $31;
    nop;
}
