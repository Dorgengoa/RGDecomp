#include "types.h"

extern void Free_130e30(void);
extern void OperatorDelete_100840(void);

asm void IosBaseDtor_102970(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    daddu      $18, $4, $0;
    sq         $16, 0x0($29);
    beqz       $18, L00102A08;
    daddu     $17, $5, $0;
    lui        $2, 0x47;
    addiu      $2, $2, -0x260;
    sw         $2, 0x0($18);
    lw         $16, 0x8($18);
    beqz       $16, L001029D8;
    nop;
    lw         $2, 0x4($18);
  L001029AC:
    addiu      $16, $16, -0x1;
    sll        $3, $16, 3;
    daddu      $4, $0, $0;
    addu       $2, $2, $3;
    lw         $6, 0x4($2);
    lw         $2, 0x0($2);
    jalr $31, $2;
    daddu     $5, $18, $0;
    bnel       $16, $0, L001029AC;
    lw        $2, 0x4($18);
    nop;
  L001029D8:
    jal        Free_130e30;
    lw        $4, 0x18($18);
    jal        Free_130e30;
    lw        $4, 0x10($18);
    jal        Free_130e30;
    lw        $4, 0x4($18);
    dsll32     $2, $17, 16;
    dsra32     $2, $2, 16;
    blezl      $2, L00102A0C;
    daddu     $2, $18, $0;
    jal        OperatorDelete_100840;
    daddu     $4, $18, $0;
  L00102A08:
    daddu      $2, $18, $0;
  L00102A0C:
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

