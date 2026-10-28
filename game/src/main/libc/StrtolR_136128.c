#include "types.h"

extern void UModDi3_13a430(void);
extern void UDivDi3_139eb0(void);
extern void MulDi3_139110(void);

asm void StrtolR_136128(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $21, 0x38($29);
    daddu      $21, $5, $0;
    sd         $16, 0x10($29);
    sd         $17, 0x18($29);
    sd         $20, 0x30($29);
    sd         $22, 0x40($29);
    sd         $31, 0x58($29);
    sw         $4, 0x0($29);
    sd         $18, 0x20($29);
    daddu      $18, $21, $0;
    sd         $19, 0x28($29);
    daddu      $19, $7, $0;
    sd         $23, 0x48($29);
    daddu      $23, $0, $0;
    sd         $30, 0x50($29);
    daddu      $30, $6, $0;
    nop;
  L00136170:
    lb         $17, 0x0($18);
    lui        $2, 0x45;
    addu       $2, $2, $17;
    lbu        $2, 0x7E91($2);
    andi       $2, $2, 0x8;
    nop;
    nop;
    bnez       $2, L00136170;
    addiu     $18, $18, 0x1;
    addiu      $2, $0, 0x2D;
    bne        $17, $2, L001361B0;
    addiu     $2, $0, 0x2B;
    lb         $17, 0x0($18);
    addiu      $18, $18, 0x1;
    b          L001361C0;
    addiu     $23, $0, 0x1;
  L001361B0:
    bne        $17, $2, L001361C0;
    nop;
    lb         $17, 0x0($18);
    addiu      $18, $18, 0x1;
  L001361C0:
    beqz       $19, L001361D0;
    addiu     $2, $0, 0x10;
    bne        $19, $2, L001361FC;
    nop;
  L001361D0:
    addiu      $2, $0, 0x30;
    bne        $17, $2, L001361FC;
    addiu     $2, $0, 0x78;
    lb         $3, 0x0($18);
    beq        $3, $2, L001361F0;
    addiu     $2, $0, 0x58;
    bne        $3, $2, L001361FC;
    nop;
  L001361F0:
    lb         $17, 0x1($18);
    addiu      $18, $18, 0x2;
    addiu      $19, $0, 0x10;
  L001361FC:
    bnez       $19, L00136210;
    addiu     $3, $0, 0xA;
    addiu      $19, $0, 0x8;
    xori       $2, $17, 0x30;
    movn       $19, $3, $2;
  L00136210:
    addiu      $2, $0, -0x1;
    dsrl       $2, $2, 1;
    ori        $20, $0, 0x8000;
    dsll32     $20, $20, 16;
    movz       $20, $2, $23;
    daddu      $16, $19, $0;
    daddu      $4, $20, $0;
    jal        UModDi3_13a430;
    daddu     $5, $16, $0;
    daddu      $4, $20, $0;
    dsll32     $22, $2, 0;
    dsra32     $22, $22, 0;
    jal        UDivDi3_139eb0;
    daddu     $5, $16, $0;
    daddu      $6, $0, $0;
    daddu      $20, $2, $0;
    b          L001362A8;
    daddu     $5, $0, $0;
  L00136258:
    slt        $2, $17, $19;
    beqz       $2, L001362E8;
    nop;
    bltz       $6, L00136288;
    sltu      $2, $20, $5;
    bnel       $2, $0, L001362A0;
    addiu     $6, $0, -0x1;
    bne        $5, $20, L00136290;
    daddu     $4, $5, $0;
    slt        $2, $22, $17;
    beqz       $2, L00136290;
    nop;
  L00136288:
    b          L001362A0;
    addiu     $6, $0, -0x1;
  L00136290:
    jal        MulDi3_139110;
    daddu     $5, $16, $0;
    addiu      $6, $0, 0x1;
    daddu      $5, $17, $2;
  L001362A0:
    lb         $17, 0x0($18);
    addiu      $18, $18, 0x1;
  L001362A8:
    lui        $4, 0x45;
    addu       $4, $4, $17;
    lbu        $4, 0x7E91($4);
    andi       $2, $4, 0x4;
    beqz       $2, L001362C8;
    andi      $2, $4, 0x3;
    b          L00136258;
    addiu     $17, $17, -0x30;
  L001362C8:
    beqz       $2, L001362E8;
    addiu     $2, $17, -0x37;
    addiu      $3, $17, -0x57;
    andi       $4, $4, 0x1;
    daddu      $17, $2, $0;
    b          L00136258;
    movz      $17, $3, $4;
    nop;
  L001362E8:
    bgez       $6, L00136318;
    dsubu     $2, $0, $5;
    addiu      $3, $0, -0x1;
    dsrl       $3, $3, 1;
    ori        $5, $0, 0x8000;
    dsll32     $5, $5, 16;
    movz       $5, $3, $23;
    lw         $3, 0x0($29);
    addiu      $2, $0, 0x22;
    b          L0013631C;
    sw        $2, 0x0($3);
    nop;
  L00136318:
    movn       $5, $2, $23;
  L0013631C:
    beqz       $30, L0013632C;
    addiu     $2, $18, -0x1;
    movn       $21, $2, $6;
    sw         $21, 0x0($30);
  L0013632C:
    ld         $16, 0x10($29);
    daddu      $2, $5, $0;
    ld         $17, 0x18($29);
    ld         $18, 0x20($29);
    ld         $19, 0x28($29);
    ld         $20, 0x30($29);
    ld         $21, 0x38($29);
    ld         $22, 0x40($29);
    ld         $23, 0x48($29);
    ld         $30, 0x50($29);
    ld         $31, 0x58($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

