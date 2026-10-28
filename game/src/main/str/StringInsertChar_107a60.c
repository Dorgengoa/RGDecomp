#include "types.h"

extern void StringReplace_106f90(void);

asm void StringInsertChar_107a60(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    daddu      $18, $4, $0;
    sq         $16, 0x0($29);
    sb         $7, 0x53($29);
    lw         $2, 0x0($5);
    andi       $2, $2, 0x1;
    beqz       $2, L00107A94;
    daddu     $17, $5, $0;
    b          L00107A98;
    lw        $4, 0x8($17);
  L00107A94:
    addiu      $4, $17, 0x1;
  L00107A98:
    dsll32     $3, $6, 0;
    addiu      $2, $29, 0x5C;
    dsra32     $3, $3, 0;
    lb         $9, 0x0($2);
    subu       $16, $3, $4;
    daddu      $6, $0, $0;
    daddu      $4, $17, $0;
    daddu      $5, $16, $0;
    addiu      $7, $29, 0x53;
    jal        StringReplace_106f90;
    addiu     $8, $29, 0x54;
    lw         $3, 0x0($17);
    andi       $3, $3, 0x1;
    beql       $3, $0, L00107AD8;
    addiu     $3, $17, 0x1;
    lw         $3, 0x8($17);
  L00107AD8:
    addu       $3, $3, $16;
    sw         $3, 0x0($18);
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

