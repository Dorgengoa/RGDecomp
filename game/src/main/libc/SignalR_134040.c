#include "types.h"

extern void InitSignalR_133fd0(void);

asm void SignalR_134040(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sltiu      $2, $17, 0x20;
    sd         $16, 0x0($29);
    sd         $18, 0x10($29);
    daddu      $18, $6, $0;
    sd         $31, 0x18($29);
    bnez       $2, L00134078;
    daddu     $16, $4, $0;
    addiu      $3, $0, 0x16;
    addiu      $2, $0, -0x1;
    b          L001340A8;
    sw        $3, 0x0($16);
  L00134078:
    lw         $2, 0x1D4($16);
    bnez       $2, L0013409C;
    sll       $3, $17, 2;
    jal        InitSignalR_133fd0;
    nop;
    bnez       $2, L001340A8;
    addiu     $2, $0, -0x1;
    lw         $2, 0x1D4($16);
    sll        $3, $17, 2;
  L0013409C:
    addu       $3, $3, $2;
    lw         $2, 0x0($3);
    sw         $18, 0x0($3);
  L001340A8:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

