#include "types.h"

asm void FpaddParts_13b140(void)
{
    .set noreorder;
    daddu      $11, $4, $0;
    lw         $7, 0x0($11);
    sltiu      $3, $7, 0x2;
    bnez       $3, L0013B394;
    daddu     $2, $11, $0;
    lw         $4, 0x0($5);
    sltiu      $3, $4, 0x2;
    bnez       $3, L0013B394;
    daddu     $2, $5, $0;
    xori       $2, $7, 0x4;
    bnez       $2, L0013B198;
    xori      $3, $4, 0x4;
    xori       $2, $4, 0x4;
    bnez       $2, L0013B1E8;
    nop;
    lw         $3, 0x4($5);
    lw         $2, 0x4($11);
    beq        $2, $3, L0013B1E8;
    nop;
    lui        $2, 0x46;
    jr         $31;
    addiu     $2, $2, -0x75C8;
  L0013B198:
    beqz       $3, L0013B394;
    daddu     $2, $5, $0;
    xori       $2, $4, 0x2;
    bnez       $2, L0013B1F0;
    xori      $3, $7, 0x2;
    xori       $2, $7, 0x2;
    bnez       $2, L0013B1E8;
    nop;
    ld         $4, 0x0($11);
    daddu      $2, $6, $0;
    sd         $4, 0x0($6);
    ld         $3, 0x8($11);
    sd         $3, 0x8($6);
    ld         $4, 0x10($11);
    sd         $4, 0x10($6);
    lw         $3, 0x4($11);
    lw         $4, 0x4($5);
    and        $3, $3, $4;
    jr         $31;
    sw        $3, 0x4($6);
  L0013B1E8:
    jr         $31;
    daddu     $2, $11, $0;
  L0013B1F0:
    beqz       $3, L0013B394;
    daddu     $2, $5, $0;
    lw         $8, 0x8($11);
    lw         $7, 0x8($5);
    ld         $10, 0x10($11);
    subu       $2, $8, $7;
    negu       $4, $2;
    slti       $3, $2, 0x0;
    movn       $2, $4, $3;
    slti       $2, $2, 0x40;
    beqz       $2, L0013B290;
    ld        $9, 0x10($5);
    slt        $2, $7, $8;
    beqz       $2, L0013B25C;
    slt       $2, $8, $7;
    addiu      $4, $0, 0x1;
    subu       $7, $8, $7;
    nop;
  L0013B238:
    dsrl       $3, $9, 1;
    and        $2, $9, $4;
    addiu      $7, $7, -0x1;
    nop;
    nop;
    bnez       $7, L0013B238;
    or        $9, $2, $3;
    daddu      $7, $8, $0;
    slt        $2, $8, $7;
  L0013B25C:
    beql       $2, $0, L0013B2B0;
    lw        $4, 0x4($11);
    addiu      $12, $0, 0x1;
  L0013B268:
    addiu      $8, $8, 0x1;
    dsrl       $2, $10, 1;
    and        $3, $10, $12;
    slt        $4, $8, $7;
    nop;
    bnez       $4, L0013B268;
    or        $10, $3, $2;
    b          L0013B2B0;
    lw        $4, 0x4($11);
    nop;
  L0013B290:
    slt        $2, $7, $8;
    beql       $2, $0, L0013B2A8;
    daddu     $8, $7, $0;
    b          L0013B2AC;
    daddu     $9, $0, $0;
    nop;
  L0013B2A8:
    daddu      $10, $0, $0;
  L0013B2AC:
    lw         $4, 0x4($11);
  L0013B2B0:
    lw         $2, 0x4($5);
    beq        $4, $2, L0013B348;
    dsubu     $2, $10, $9;
    dsubu      $3, $9, $10;
    movz       $3, $2, $4;
    bltzl      $3, L0013B2E0;
    dsubu     $3, $0, $3;
    sw         $8, 0x8($6);
    sd         $3, 0x10($6);
    b          L0013B2F0;
    sw        $0, 0x4($6);
    nop;
  L0013B2E0:
    addiu      $2, $0, 0x1;
    sw         $2, 0x4($6);
    sw         $8, 0x8($6);
    sd         $3, 0x10($6);
  L0013B2F0:
    ld         $7, 0x10($6);
    addiu      $2, $0, -0x1;
    dsll       $2, $2, 5;
    dsrl       $2, $2, 4;
    daddiu     $3, $7, -0x1;
    sltu       $2, $2, $3;
    bnez       $2, L0013B35C;
    nop;
  L0013B310:
    dsll       $5, $7, 1;
    lw         $2, 0x8($6);
    daddiu     $3, $5, -0x1;
    addiu      $4, $0, -0x1;
    dsll       $4, $4, 5;
    dsrl       $4, $4, 4;
    addiu      $2, $2, -0x1;
    sltu       $4, $4, $3;
    sw         $2, 0x8($6);
    daddu      $7, $5, $0;
    beqz       $4, L0013B310;
    sd        $5, 0x10($6);
    b          L0013B35C;
    nop;
  L0013B348:
    daddu      $2, $10, $9;
    sw         $4, 0x4($6);
    sw         $8, 0x8($6);
    daddu      $7, $2, $0;
    sd         $2, 0x10($6);
  L0013B35C:
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 3;
    addiu      $3, $0, 0x3;
    sltu       $2, $2, $7;
    beqz       $2, L0013B390;
    sw        $3, 0x0($6);
    lw         $2, 0x8($6);
    dsrl       $4, $7, 1;
    andi       $3, $7, 0x1;
    or         $3, $3, $4;
    addiu      $2, $2, 0x1;
    sd         $3, 0x10($6);
    sw         $2, 0x8($6);
  L0013B390:
    daddu      $2, $6, $0;
  L0013B394:
    jr         $31;
    nop;
}

