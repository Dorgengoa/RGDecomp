#include "types.h"

extern void Srget_133f30(void);
extern void memcpy(void);
extern void Ungetc_1364e8(void);

asm void WFilebufGetBytesPeekMaybe_105ce0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $31, 0x50($29);
    sq         $20, 0x40($29);
    sq         $19, 0x30($29);
    daddu      $20, $4, $0;
    sq         $18, 0x20($29);
    daddu      $19, $5, $0;
    sq         $17, 0x10($29);
    sltiu      $1, $19, 0xD;
    sq         $16, 0x0($29);
    bnez       $1, L00105D18;
    daddu     $18, $6, $0;
    b          L00105DD4;
    addiu     $2, $0, -0x1;
  L00105D18:
    blez       $19, L00105D80;
    daddu     $17, $0, $0;
    addiu      $16, $29, 0x60;
  L00105D24:
    lw         $3, 0x1C($20);
    lw         $2, 0x4($3);
    addiu      $2, $2, -0x1;
    bgez       $2, L00105D48;
    sw        $2, 0x4($3);
    jal        Srget_133f30;
    lw        $4, 0x1C($20);
    b          L00105D60;
    addiu     $3, $0, -0x1;
  L00105D48:
    lw         $4, 0x1C($20);
    lw         $3, 0x0($4);
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($4);
    lbu        $2, 0x0($3);
    addiu      $3, $0, -0x1;
  L00105D60:
    bnel       $2, $3, L00105D70;
    sb        $2, 0x0($16);
    b          L00105DD4;
    daddu     $2, $3, $0;
  L00105D70:
    addiu      $17, $17, 0x1;
    slt        $2, $17, $19;
    bnez       $2, L00105D24;
    addiu     $16, $16, 0x1;
  L00105D80:
    addiu      $4, $29, 0x6C;
    addiu      $5, $29, 0x60;
    jal        memcpy;
    daddu     $6, $19, $0;
    beqz       $18, L00105DD0;
    nop;
    blez       $19, L00105DD0;
    nop;
    addiu      $19, $19, -0x1;
  L00105DA4:
    addu       $2, $19, $29;
    lb         $4, 0x60($2);
    jal        Ungetc_1364e8;
    lw        $5, 0x1C($20);
    addiu      $3, $0, -0x1;
    bne        $2, $3, L00105DC8;
    nop;
    b          L00105DD4;
    daddu     $2, $3, $0;
  L00105DC8:
    bgtzl      $19, L00105DA4;
    addiu     $19, $19, -0x1;
  L00105DD0:
    lhu        $2, 0x6C($29);
  L00105DD4:
    ld         $31, 0x50($29);
    lq         $20, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

