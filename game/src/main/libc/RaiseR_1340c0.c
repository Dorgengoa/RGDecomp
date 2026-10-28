#include "types.h"

extern void InitSignalR_133fd0(void);
extern void GetpidR_134318(void);
extern void KillR_1342b8(void);

asm void RaiseR_1340c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sltiu      $2, $17, 0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    bnez       $2, L001340F0;
    daddu     $16, $4, $0;
    addiu      $3, $0, 0x16;
    addiu      $2, $0, -0x1;
    b          L00134184;
    sw        $3, 0x0($16);
  L001340F0:
    lw         $3, 0x1D4($16);
    bnez       $3, L00134114;
    sll       $2, $17, 2;
    jal        InitSignalR_133fd0;
    nop;
    bnez       $2, L00134184;
    addiu     $2, $0, -0x1;
    lw         $3, 0x1D4($16);
    sll        $2, $17, 2;
  L00134114:
    addu       $4, $2, $3;
    lw         $5, 0x0($4);
    bnel       $5, $0, L00134150;
    addiu     $3, $0, 0x1;
    jal        GetpidR_134318;
    daddu     $4, $16, $0;
    daddu      $4, $16, $0;
    daddu      $6, $17, $0;
    ld         $17, 0x8($29);
    ld         $16, 0x0($29);
    daddu      $5, $2, $0;
    ld         $31, 0x10($29);
    j          KillR_1342b8;
    addiu     $29, $29, 0x20;
    nop;
  L00134150:
    beq        $5, $3, L00134184;
    daddu     $2, $0, $0;
    addiu      $2, $0, -0x1;
    bnel       $5, $2, L00134178;
    sw        $0, 0x0($4);
    addiu      $3, $0, 0x16;
    addiu      $2, $0, 0x1;
    b          L00134184;
    sw        $3, 0x0($16);
    nop;
  L00134178:
    jalr $31, $5;
    daddu     $4, $17, $0;
    daddu      $2, $0, $0;
  L00134184:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

