#include "types.h"

extern void Balloc_131cf0(void);
extern void Multadd_131dc8(void);

asm void S2b_131ed0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $2, $0, 0x9;
    sd         $20, 0x20($29);
    daddu      $20, $7, $0;
    addiu      $3, $20, 0x8;
    addiu      $7, $0, 0x1;
    div $3, $2;
    sd         $16, 0x0($29);
    sd         $17, 0x8($29);
    daddu      $17, $8, $0;
    sd         $18, 0x10($29);
    daddu      $18, $6, $0;
    sd         $19, 0x18($29);
    daddu      $19, $4, $0;
    sd         $31, 0x28($29);
    beql       $2, $0, L00131F14;
        .word 0x000001CD;
  L00131F14:
    daddu      $16, $5, $0;
    mflo       $3;
    slt        $2, $7, $3;
    beqz       $2, L00131F44;
    daddu     $5, $0, $0;
  L00131F28:
    sll        $7, $7, 1;
    slt        $2, $7, $3;
    nop;
    nop;
    nop;
    bnez       $2, L00131F28;
    addiu     $5, $5, 0x1;
  L00131F44:
    jal        Balloc_131cf0;
    daddu     $4, $19, $0;
    slti       $3, $18, 0xA;
    daddu      $5, $2, $0;
    addiu      $2, $0, 0x1;
    sw         $17, 0x14($5);
    addiu      $17, $0, 0x9;
    bnez       $3, L00131FA0;
    sw        $2, 0x10($5);
    addiu      $16, $16, 0x9;
    lb         $7, 0x0($16);
  L00131F70:
    addiu      $16, $16, 0x1;
    daddu      $4, $19, $0;
    addiu      $6, $0, 0xA;
    addiu      $7, $7, -0x30;
    jal        Multadd_131dc8;
    addiu     $17, $17, 0x1;
    daddu      $5, $2, $0;
    slt        $2, $17, $18;
    bnel       $2, $0, L00131F70;
    lb        $7, 0x0($16);
    b          L00131FA4;
    addiu     $16, $16, 0x1;
  L00131FA0:
    addiu      $16, $16, 0xA;
  L00131FA4:
    slt        $2, $17, $20;
    beql       $2, $0, L00131FE0;
    ld        $16, 0x0($29);
    subu       $17, $20, $17;
    nop;
  L00131FB8:
    lb         $7, 0x0($16);
    addiu      $16, $16, 0x1;
    daddu      $4, $19, $0;
    addiu      $6, $0, 0xA;
    addiu      $7, $7, -0x30;
    jal        Multadd_131dc8;
    addiu     $17, $17, -0x1;
    bnez       $17, L00131FB8;
    daddu     $5, $2, $0;
    ld         $16, 0x0($29);
  L00131FE0:
    daddu      $2, $5, $0;
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

