#include "types.h"

extern void dpsub(void);
extern void DtoaR_12e268(void);
extern void DoubleCmp_13b948(void);

asm void VfprintfCvt_138bc8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    addiu      $2, $0, 0x66;
    sd         $17, 0x18($29);
    daddu      $17, $10, $0;
    sd         $16, 0x10($29);
    daddu      $16, $8, $0;
    sd         $18, 0x20($29);
    daddu      $18, $5, $0;
    sd         $19, 0x28($29);
    daddu      $19, $6, $0;
    sd         $20, 0x30($29);
    addiu      $20, $0, 0x3;
    sd         $21, 0x38($29);
    daddu      $21, $9, $0;
    sd         $22, 0x40($29);
    daddu      $22, $4, $0;
    sd         $23, 0x48($29);
    daddu      $23, $7, $0;
    sd         $30, 0x50($29);
    daddu      $30, $11, $0;
    beq        $17, $2, L00138C3C;
    sd        $31, 0x58($29);
    addiu      $2, $0, 0x65;
    beq        $17, $2, L00138C34;
    addiu     $2, $0, 0x45;
    bne        $17, $2, L00138C3C;
    addiu     $20, $0, 0x2;
  L00138C34:
    addiu      $19, $19, 0x1;
    addiu      $20, $0, 0x2;
  L00138C3C:
    daddu      $2, $18, $0;
    dsra32     $2, $2, 0;
    bgezl      $2, L00138C68;
    sb        $0, 0x0($16);
    daddu      $5, $18, $0;
    daddu      $4, $0, $0;
    jal        dpsub;
    nop;
    daddu      $18, $2, $0;
    addiu      $2, $0, 0x2D;
    sb         $2, 0x0($16);
  L00138C68:
    daddu      $6, $20, $0;
    daddu      $4, $22, $0;
    daddu      $5, $18, $0;
    daddu      $7, $19, $0;
    daddu      $8, $21, $0;
    daddu      $9, $29, $0;
    jal        DtoaR_12e268;
    addiu     $10, $29, 0x4;
    daddu      $20, $2, $0;
    addiu      $2, $0, 0x67;
    beq        $17, $2, L00138CA0;
    addiu     $2, $0, 0x47;
    bne        $17, $2, L00138CAC;
    addiu     $2, $0, 0x66;
  L00138CA0:
    andi       $2, $23, 0x1;
    beqz       $2, L00138D48;
    addiu     $2, $0, 0x66;
  L00138CAC:
    bne        $17, $2, L00138CEC;
    addu      $16, $20, $19;
    lb         $3, 0x0($20);
    addiu      $2, $0, 0x30;
    bnel       $3, $2, L00138CE8;
    lw        $2, 0x0($21);
    daddu      $4, $18, $0;
    daddu      $5, $0, $0;
    jal        DoubleCmp_13b948;
    nop;
    beqz       $2, L00138CE4;
    addiu     $2, $0, 0x1;
    subu       $2, $2, $19;
    sw         $2, 0x0($21);
  L00138CE4:
    lw         $2, 0x0($21);
  L00138CE8:
    addu       $16, $16, $2;
  L00138CEC:
    daddu      $4, $18, $0;
    daddu      $5, $0, $0;
    jal        DoubleCmp_13b948;
    nop;
    lw         $3, 0x4($29);
    xori       $2, $2, 0x0;
    movz       $3, $16, $2;
    sltu       $2, $3, $16;
    sw         $3, 0x4($29);
    beqz       $2, L00138D4C;
    daddu     $4, $3, $0;
    addiu      $5, $0, 0x30;
    nop;
  L00138D20:
    addiu      $3, $4, 0x1;
    sb         $5, 0x0($4);
    sltu       $2, $3, $16;
    sw         $3, 0x4($29);
    nop;
    bnez       $2, L00138D20;
    daddu     $4, $3, $0;
    b          L00138D50;
    subu      $3, $3, $20;
    nop;
  L00138D48:
    lw         $3, 0x4($29);
  L00138D4C:
    subu       $3, $3, $20;
  L00138D50:
    daddu      $2, $20, $0;
    sw         $3, 0x0($30);
    ld         $16, 0x10($29);
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

