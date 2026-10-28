#include "types.h"

extern void KernelExitThunk_120d18(void);

asm void Exit_12f4e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $20, 0x20($29);
    lui        $20, 0x45;
    sd         $19, 0x18($29);
    sd         $16, 0x0($29);
    sd         $17, 0x8($29);
    sd         $18, 0x10($29);
    sd         $31, 0x28($29);
    lw         $2, -0x67A8($20);
    lw         $18, 0x148($2);
    beqz       $18, L0012F550;
    daddu     $19, $4, $0;
    lw         $16, 0x4($18);
    nop;
  L0012F518:
    addiu      $16, $16, -0x1;
    bltz       $16, L0012F544;
    addiu     $3, $18, 0x8;
    sll        $2, $16, 2;
    addu       $17, $2, $3;
    lw         $2, 0x0($17);
  L0012F530:
    addiu      $17, $17, -0x4;
    jalr $31, $2;
    addiu     $16, $16, -0x1;
    bgezl      $16, L0012F530;
    lw        $2, 0x0($17);
  L0012F544:
    lw         $18, 0x0($18);
    bnel       $18, $0, L0012F518;
    lw        $16, 0x4($18);
  L0012F550:
    lw         $4, -0x67A8($20);
    lw         $2, 0x3C($4);
    beql       $2, $0, L0012F56C;
    daddu     $4, $19, $0;
    jalr $31, $2;
    nop;
    daddu      $4, $19, $0;
  L0012F56C:
    ld         $19, 0x18($29);
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    j          KernelExitThunk_120d18;
    addiu     $29, $29, 0x30;
}

