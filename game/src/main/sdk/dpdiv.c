#include "types.h"

extern void UnpackD_13b080(void);
extern void PackD_13afa8(void);

asm void dpdiv(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $4, 0x40($29);
    addiu      $4, $29, 0x40;
    sd         $5, 0x48($29);
    sd         $16, 0x50($29);
    sd         $31, 0x58($29);
    jal        UnpackD_13b080;
    daddu     $5, $29, $0;
    addiu      $16, $29, 0x20;
    addiu      $4, $29, 0x48;
    jal        UnpackD_13b080;
    daddu     $5, $16, $0;
    lw         $6, 0x0($29);
    daddu      $8, $29, $0;
    sltiu      $2, $6, 0x2;
    bnez       $2, L0013B810;
    daddu     $4, $29, $0;
    lw         $5, 0x20($29);
    sltiu      $2, $5, 0x2;
    bnez       $2, L0013B810;
    daddu     $4, $16, $0;
    lw         $2, 0x4($29);
    xori       $4, $6, 0x4;
    lw         $3, 0x24($29);
    xor        $2, $2, $3;
    beqz       $4, L0013B760;
    sw        $2, 0x4($29);
    xori       $2, $6, 0x2;
    bnez       $2, L0013B778;
    xori      $2, $5, 0x4;
  L0013B760:
    bnel       $6, $5, L0013B810;
    daddu     $4, $29, $0;
    lui        $2, 0x46;
    b          L0013B810;
    addiu     $4, $2, -0x75C8;
    nop;
  L0013B778:
    bnel       $2, $0, L0013B790;
    xori      $2, $5, 0x2;
    sd         $0, 0x10($29);
    daddu      $4, $29, $0;
    b          L0013B810;
    sw        $0, 0x8($29);
  L0013B790:
    bnel       $2, $0, L0013B7A8;
    lw        $3, 0x8($29);
    addiu      $2, $0, 0x4;
    daddu      $4, $29, $0;
    b          L0013B810;
    sw        $2, 0x0($29);
  L0013B7A8:
    lw         $2, 0x28($29);
    ld         $4, 0x10($29);
    ld         $6, 0x30($29);
    subu       $2, $3, $2;
    sltu       $5, $4, $6;
    beqz       $5, L0013B7D4;
    sw        $2, 0x8($29);
    addiu      $2, $2, -0x1;
    dsll       $4, $4, 1;
    sw         $2, 0x8($29);
    sltu       $5, $4, $6;
  L0013B7D4:
    ori        $3, $0, 0x8000;
    dsll32     $3, $3, 13;
    daddu      $7, $0, $0;
  L0013B7E0:
    bnez       $5, L0013B7F8;
    dsll      $2, $4, 1;
    dsubu      $4, $4, $6;
    or         $7, $7, $3;
    dsll       $2, $4, 1;
    nop;
  L0013B7F8:
    dsrl       $3, $3, 1;
    sltu       $5, $2, $6;
    bnez       $3, L0013B7E0;
    daddu     $4, $2, $0;
    sd         $7, 0x10($8);
    daddu      $4, $8, $0;
  L0013B810:
    jal        PackD_13afa8;
    nop;
    ld         $16, 0x50($29);
    ld         $31, 0x58($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

