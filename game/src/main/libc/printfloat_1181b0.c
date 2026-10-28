#include "types.h"

extern void DoubleCmp_13b948(void);
extern void dpsub(void);
extern void dpmul(void);
extern void dpdiv(void);
extern void DoubleToU64_13ab28(void);
extern void ftoi(void);
extern void FormatPrintNestedMaybe_119148(void);

asm void printfloat_1181b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $22, 0x60($29);
    sd         $21, 0x50($29);
    daddu      $22, $5, $0;
    sd         $20, 0x40($29);
    daddu      $21, $4, $0;
    sd         $18, 0x20($29);
    daddu      $20, $0, $0;
    sd         $17, 0x10($29);
    daddu      $18, $0, $0;
    sd         $16, 0x0($29);
    daddu      $17, $6, $0;
    sd         $31, 0x70($29);
    sd         $19, 0x30($29);
    lw         $2, 0x0($17);
    bnez       $2, L001181FC;
    daddu     $16, $7, $0;
    b          L00118360;
    daddu     $2, $0, $0;
  L001181FC:
    daddu      $19, $0, $0;
    daddu      $4, $16, $0;
    jal        DoubleCmp_13b948;
    daddu     $5, $19, $0;
    bgez       $2, L00118240;
    daddu     $5, $16, $0;
    jal        dpsub;
    daddu     $4, $19, $0;
    addiu      $20, $0, 0x1;
    daddu      $16, $2, $0;
    daddu      $4, $22, $0;
    daddu      $5, $17, $0;
    jalr $31, $21;
    addiu     $6, $0, 0x2D;
    lw         $3, 0x0($17);
    addiu      $3, $3, -0x1;
    sw         $3, 0x0($17);
  L00118240:
    lui        $1, 0x45;
    ld         $5, 0x6758($1);
    jal        DoubleCmp_13b948;
    daddu     $4, $16, $0;
    bgez       $2, L00118294;
    lui       $19, 0x45;
    b          L00118274;
    nop;
  L00118260:
    ori        $5, $0, 0x8048;
    dsll32     $5, $5, 15;
    jal        dpmul;
    addiu     $18, $18, -0x1;
    daddu      $16, $2, $0;
  L00118274:
    lui        $1, 0x45;
    ld         $5, 0x6760($1);
    jal        DoubleCmp_13b948;
    daddu     $4, $16, $0;
    bltz       $2, L00118260;
    daddu     $4, $16, $0;
    b          L001182E4;
    nop;
  L00118294:
    ori        $5, $0, 0xFFC0;
    dsll32     $5, $5, 14;
    jal        DoubleCmp_13b948;
    daddu     $4, $16, $0;
    bltz       $2, L001182E4;
    lui       $19, 0x45;
    b          L001182CC;
    nop;
    nop;
  L001182B8:
    ori        $5, $0, 0x8048;
    dsll32     $5, $5, 15;
    jal        dpdiv;
    addiu     $18, $18, 0x1;
    daddu      $16, $2, $0;
  L001182CC:
    ori        $5, $0, 0xFFC0;
    dsll32     $5, $5, 14;
    jal        DoubleCmp_13b948;
    daddu     $4, $16, $0;
    bgez       $2, L001182B8;
    daddu     $4, $16, $0;
  L001182E4:
    lui        $1, 0x45;
    ld         $5, 0x6768($1);
    jal        dpmul;
    daddu     $4, $16, $0;
    jal        DoubleToU64_13ab28;
    daddu     $4, $2, $0;
    jal        ftoi;
    daddu     $4, $2, $0;
    addiu      $7, $19, 0x6740;
    daddu      $8, $2, $0;
    daddu      $4, $21, $0;
    daddu      $5, $22, $0;
    jal        FormatPrintNestedMaybe_119148;
    daddu     $6, $17, $0;
    bltz       $18, L0011833C;
    addu      $20, $20, $2;
    lui        $7, 0x45;
    daddu      $4, $21, $0;
    daddu      $5, $22, $0;
    daddu      $6, $17, $0;
    b          L00118350;
    addiu     $7, $7, 0x6748;
  L0011833C:
    lui        $7, 0x45;
    daddu      $4, $21, $0;
    daddu      $5, $22, $0;
    daddu      $6, $17, $0;
    addiu      $7, $7, 0x6750;
  L00118350:
    jal        FormatPrintNestedMaybe_119148;
    daddu     $8, $18, $0;
    addu       $20, $20, $2;
    daddu      $2, $20, $0;
  L00118360:
    ld         $31, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

