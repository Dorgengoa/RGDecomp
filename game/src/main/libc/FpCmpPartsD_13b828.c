#include "types.h"

asm void FpCmpPartsD_13b828(void)
{
    .set noreorder;
    lw         $6, 0x0($4);
    sltiu      $2, $6, 0x2;
    bnez       $2, L0013B848;
    nop;
    lw         $3, 0x0($5);
    sltiu      $2, $3, 0x2;
    beql       $2, $0, L0013B850;
    xori      $2, $6, 0x4;
  L0013B848:
    jr         $31;
    addiu     $2, $0, 0x1;
  L0013B850:
    bnez       $2, L0013B870;
    xori      $2, $3, 0x4;
    bnel       $2, $0, L0013B8C4;
    lw        $4, 0x4($4);
    lw         $3, 0x4($5);
    lw         $2, 0x4($4);
    jr         $31;
    subu      $2, $3, $2;
  L0013B870:
    bnel       $2, $0, L0013B890;
    xori      $2, $6, 0x2;
    lw         $4, 0x4($5);
    addiu      $3, $0, -0x1;
    addiu      $2, $0, 0x1;
    jr         $31;
    movz      $2, $3, $4;
    nop;
  L0013B890:
    bnel       $2, $0, L0013B8B8;
    xori      $2, $3, 0x2;
    xori       $3, $3, 0x2;
    beqz       $3, L0013B940;
    daddu     $2, $0, $0;
    lw         $4, 0x4($5);
    addiu      $3, $0, 0x1;
    addiu      $2, $0, -0x1;
    jr         $31;
    movn      $2, $3, $4;
  L0013B8B8:
    bnel       $2, $0, L0013B8D8;
    lw        $7, 0x4($4);
    lw         $4, 0x4($4);
  L0013B8C4:
    addiu      $3, $0, 0x1;
    addiu      $2, $0, -0x1;
    jr         $31;
    movz      $2, $3, $4;
    nop;
  L0013B8D8:
    lw         $2, 0x4($5);
    bne        $7, $2, L0013B91C;
    addiu     $3, $0, 0x1;
    lw         $6, 0x8($4);
    lw         $3, 0x8($5);
    slt        $2, $3, $6;
    bnel       $2, $0, L0013B91C;
    addiu     $3, $0, 0x1;
    slt        $2, $6, $3;
    bnez       $2, L0013B934;
    addiu     $3, $0, -0x1;
    ld         $3, 0x10($4);
    ld         $4, 0x10($5);
    sltu       $2, $4, $3;
    beql       $2, $0, L0013B928;
    sltu      $2, $3, $4;
    addiu      $3, $0, 0x1;
  L0013B91C:
    addiu      $2, $0, -0x1;
    jr         $31;
    movz      $2, $3, $7;
  L0013B928:
    beql       $2, $0, L0013B940;
    daddu     $2, $0, $0;
    addiu      $3, $0, -0x1;
  L0013B934:
    addiu      $2, $0, 0x1;
    jr         $31;
    movz      $2, $3, $7;
  L0013B940:
    jr         $31;
    nop;
}

