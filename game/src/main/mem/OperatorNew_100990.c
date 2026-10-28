#include "types.h"

extern void Malloc_130dd8(void);
extern void ThrowException_1025c0(void);

asm void OperatorNew_100990(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x20($29);
    sq         $30, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $16, $4, $0;
    bnez       $16, L001009B0;
    addu      $30, $29, $0;
    addiu      $16, $0, 0x1;
  L001009B0:
    jal        Malloc_130dd8;
    daddu     $4, $16, $0;
    bnez       $2, L00100A40;
    nop;
  L001009C0:
    lui        $2, 0x48;
    lw         $2, 0x53C8($2);
    beqz       $2, L001009E0;
    nop;
    jalr $31, $2;
    nop;
    b          L00100A2C;
    daddu     $4, $16, $0;
  L001009E0:
    lui        $2, 0x44;
    lb         $2, 0x5E80($2);
    beqz       $2, L00100A20;
    nop;
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0x280;
    lui        $6, 0x10;
    addiu      $4, $4, 0x54E0;
    sw         $2, 0x3C($30);
    addiu      $5, $30, 0x3C;
    jal        ThrowException_1025c0;
    addiu     $6, $6, 0x920;
    b          L00100A28;
    nop;
    nop;
  L00100A20:
    b          L00100A40;
    daddu     $2, $0, $0;
  L00100A28:
    daddu      $4, $16, $0;
  L00100A2C:
    jal        Malloc_130dd8;
    nop;
    beqz       $2, L001009C0;
    nop;
    nop;
  L00100A40:
    addu       $29, $30, $0;
    ld         $31, 0x20($29);
    lq         $30, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

