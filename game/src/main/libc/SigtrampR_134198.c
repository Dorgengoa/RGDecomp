#include "types.h"

extern void InitSignalR_133fd0(void);

asm void SigtrampR_134198(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $2, $0, -0x1;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sltiu      $3, $16, 0x20;
    sd         $17, 0x8($29);
    sd         $31, 0x10($29);
    beqz       $3, L0013421C;
    daddu     $17, $4, $0;
    lw         $5, 0x1D4($17);
    bnez       $5, L001341E4;
    sll       $3, $16, 2;
    jal        InitSignalR_133fd0;
    nop;
    beql       $2, $0, L001341E0;
    lw        $5, 0x1D4($17);
    b          L0013421C;
    addiu     $2, $0, -0x1;
  L001341E0:
    sll        $3, $16, 2;
  L001341E4:
    addu       $4, $3, $5;
    lw         $5, 0x0($4);
    beqz       $5, L0013421C;
    addiu     $2, $0, 0x1;
    addiu      $3, $0, -0x1;
    beq        $5, $3, L0013421C;
    addiu     $2, $0, 0x2;
    addiu      $3, $0, 0x1;
    beq        $5, $3, L0013421C;
    addiu     $2, $0, 0x3;
    sw         $0, 0x0($4);
    jalr $31, $5;
    daddu     $4, $16, $0;
    daddu      $2, $0, $0;
  L0013421C:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

