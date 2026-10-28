#include "types.h"

extern void QueuePeekReadDone(void);

asm void sceTtyRead(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    daddu      $3, $0, $0;
    sd         $20, 0x40($29);
    sd         $18, 0x20($29);
    daddu      $20, $4, $0;
    sd         $31, 0x50($29);
    daddu      $18, $5, $0;
    sd         $19, 0x30($29);
    sd         $17, 0x10($29);
    blez       $18, L00117F1C;
    sd        $16, 0x0($29);
    lui        $19, 0x48;
    lui        $2, 0x48;
    nop;
  L00117EA8:
    addiu      $17, $3, 0x1;
    lw         $4, 0x6528($2);
    addu       $16, $20, $3;
    nop;
  L00117EB8:
    lw         $2, 0x4($4);
    nop;
    nop;
    nop;
    nop;
    beqz       $2, L00117EB8;
    nop;
    addiu      $5, $19, 0x6510;
    lw         $2, 0x18($5);
    lw         $3, 0x8($2);
    lbu        $4, 0x0($3);
    sb         $4, 0x0($16);
    jal        QueuePeekReadDone;
    lw        $4, 0x18($5);
    lb         $3, 0x0($16);
    addiu      $2, $0, 0xA;
    beq        $3, $2, L00117F08;
    addiu     $2, $0, 0xD;
    bne        $3, $2, L00117F10;
    daddu     $3, $17, $0;
  L00117F08:
    b          L00117F20;
    daddu     $2, $17, $0;
  L00117F10:
    slt        $2, $3, $18;
    bnez       $2, L00117EA8;
    lui       $2, 0x48;
  L00117F1C:
    daddu      $2, $3, $0;
  L00117F20:
    ld         $31, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
