#include "types.h"

extern void PackD_13afa8(void);

asm void litodp(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $2, $0, 0x3;
    srl        $3, $4, 31;
    sd         $31, 0x20($29);
    sw         $2, 0x0($29);
    bnez       $4, L0013B9C0;
    sw        $3, 0x4($29);
    addiu      $2, $0, 0x2;
    b          L0013BA3C;
    sw        $2, 0x0($29);
  L0013B9C0:
    addiu      $2, $0, 0x3C;
    beqz       $3, L0013B9F0;
    sw        $2, 0x8($29);
    lui        $3, (0x80000000 >> 16);
    ori        $2, $0, 0xC1E0;
    dsll32     $2, $2, 16;
    beq        $4, $3, L0013BA48;
    ld        $31, 0x20($29);
    negu       $2, $4;
    b          L0013B9F4;
    sd        $2, 0x10($29);
    nop;
  L0013B9F0:
    sd         $4, 0x10($29);
  L0013B9F4:
    ld         $4, 0x10($29);
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 4;
    sltu       $2, $2, $4;
    bnez       $2, L0013BA3C;
    lw        $5, 0x8($29);
    addiu      $6, $0, -0x1;
    dsrl       $6, $6, 4;
    nop;
  L0013BA18:
    dsll       $3, $4, 1;
    addiu      $5, $5, -0x1;
    sltu       $2, $6, $3;
    nop;
    nop;
    beqz       $2, L0013BA18;
    daddu     $4, $3, $0;
    sw         $5, 0x8($29);
    sd         $3, 0x10($29);
  L0013BA3C:
    jal        PackD_13afa8;
    daddu     $4, $29, $0;
    ld         $31, 0x20($29);
  L0013BA48:
    jr         $31;
    addiu     $29, $29, 0x30;
}

