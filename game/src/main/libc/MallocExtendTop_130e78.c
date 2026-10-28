#include "types.h"

extern void SbrkR_133f78(void);
extern void FreeR_12f9f8(void);

asm void MallocExtendTop_130e78(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    lui        $2, 0x45;
    sd         $23, 0x48($29);
    addiu      $23, $2, -0x6798;
    sd         $16, 0x10($29);
    lui        $6, 0x45;
    sd         $18, 0x20($29);
    lui        $2, 0x45;
    sd         $19, 0x28($29);
    dsll32     $5, $5, 0;
    sd         $20, 0x30($29);
    dsrl32     $5, $5, 0;
    sd         $21, 0x38($29);
    addiu      $21, $0, -0x1;
    sd         $22, 0x40($29);
    addiu      $22, $2, -0x6380;
    lw         $20, 0x8($23);
    addiu      $2, $0, -0x4;
    sd         $17, 0x18($29);
    sd         $30, 0x50($29);
    sd         $31, 0x58($29);
    ld         $3, -0x6388($6);
    lw         $6, 0x4($20);
    daddu      $5, $5, $3;
    lw         $3, 0x0($22);
    and        $19, $6, $2;
    daddiu     $5, $5, 0x10;
    dsll32     $18, $5, 0;
    dsra32     $18, $18, 0;
    sw         $4, 0x0($29);
    beq        $3, $21, L00130F14;
    addu      $16, $20, $19;
    dsll32     $2, $18, 0;
    addiu      $3, $0, -0x1000;
    dsrl32     $2, $2, 0;
    daddiu     $2, $2, 0xFFF;
    and        $2, $2, $3;
    dsll32     $18, $2, 0;
    dsra32     $18, $18, 0;
  L00130F14:
    jal        SbrkR_133f78;
    daddu     $5, $18, $0;
    daddu      $17, $2, $0;
    beq        $17, $21, L001310A0;
    sltu      $2, $17, $16;
    beqz       $2, L00130F3C;
    lui       $30, 0x45;
    bnel       $20, $23, L001310A4;
    ld        $16, 0x10($29);
    lui        $30, 0x45;
  L00130F3C:
    addiu      $4, $30, -0x6368;
    lw         $2, 0x0($4);
    addu       $3, $2, $18;
    bne        $17, $16, L00130F68;
    sw        $3, 0x0($4);
    addu       $4, $18, $19;
    lw         $3, 0x8($23);
    ori        $2, $4, 0x1;
    b          L0013106C;
    sw        $2, 0x4($3);
    nop;
  L00130F68:
    lw         $2, 0x0($22);
    bne        $2, $21, L00130F80;
    subu      $2, $17, $16;
    b          L00130F88;
    sw        $17, 0x0($22);
    nop;
  L00130F80:
    addu       $2, $3, $2;
    sw         $2, 0x0($4);
  L00130F88:
    addiu      $2, $17, 0x8;
    andi       $5, $2, 0xF;
    beqz       $5, L00130FA8;
    addiu     $2, $0, 0x10;
    subu       $16, $2, $5;
    b          L00130FAC;
    addu      $17, $17, $16;
    nop;
  L00130FA8:
    daddu      $16, $0, $0;
  L00130FAC:
    addu       $2, $17, $18;
    addiu      $3, $0, 0x1000;
    andi       $2, $2, 0xFFF;
    lw         $4, 0x0($29);
    dsubu      $3, $3, $2;
    dsll32     $3, $3, 0;
    dsra32     $3, $3, 0;
    addu       $16, $16, $3;
    jal        SbrkR_133f78;
    daddu     $5, $16, $0;
    daddu      $4, $2, $0;
    addiu      $2, $0, -0x1;
    beq        $4, $2, L001310A0;
    subu      $4, $4, $17;
    addiu      $5, $30, -0x6368;
    lw         $2, 0x0($5);
    addu       $4, $4, $16;
    lui        $6, 0x45;
    ori        $4, $4, 0x1;
    addiu      $3, $6, -0x6798;
    addu       $2, $2, $16;
    sw         $2, 0x0($5);
    sw         $17, 0x8($3);
    beq        $20, $3, L0013106C;
    sw        $4, 0x4($17);
    sltiu      $2, $19, 0x10;
    beql       $2, $0, L00131030;
    lw        $2, 0x4($20);
    daddu      $3, $17, $0;
    addiu      $2, $0, 0x1;
    b          L001310A0;
    sw        $2, 0x4($3);
    nop;
  L00131030:
    addiu      $4, $19, -0xC;
    addiu      $3, $0, -0x10;
    addiu      $5, $0, 0x5;
    and        $19, $4, $3;
    andi       $2, $2, 0x1;
    addu       $3, $20, $19;
    or         $2, $2, $19;
    sltiu      $4, $19, 0x10;
    sw         $2, 0x4($20);
    sw         $5, 0x8($3);
    bnez       $4, L0013106C;
    sw        $5, 0x4($3);
    lw         $4, 0x0($29);
    jal        FreeR_12f9f8;
    addiu     $5, $20, 0x8;
  L0013106C:
    lui        $3, 0x45;
    lw         $5, -0x6368($30);
    addiu      $3, $3, -0x6378;
    ld         $2, 0x0($3);
    sltu       $2, $2, $5;
    bnel       $2, $0, L00131088;
    sd        $5, 0x0($3);
  L00131088:
    lui        $3, 0x45;
    addiu      $3, $3, -0x6370;
    ld         $2, 0x0($3);
    sltu       $2, $2, $5;
    bnel       $2, $0, L001310A0;
    sd        $5, 0x0($3);
  L001310A0:
    ld         $16, 0x10($29);
  L001310A4:
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
