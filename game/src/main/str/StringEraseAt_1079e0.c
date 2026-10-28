#include "types.h"

extern void StringReplace_106f90(void);

asm void StringEraseAt_1079e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $6, $0;
    lw         $2, 0x0($5);
    andi       $2, $2, 0x1;
    beqz       $2, L00107A0C;
    daddu     $16, $4, $0;
    b          L00107A10;
    lw        $3, 0x8($5);
  L00107A0C:
    addiu      $3, $5, 0x1;
  L00107A10:
    dsll32     $2, $17, 0;
    lb         $9, 0x3C($29);
    dsra32     $2, $2, 0;
    daddu      $4, $5, $0;
    subu       $5, $2, $3;
    addiu      $6, $0, 0x1;
    daddu      $7, $0, $0;
    jal        StringReplace_106f90;
    daddu     $8, $0, $0;
    dsll32     $3, $17, 0;
    dsra32     $3, $3, 0;
    sw         $3, 0x0($16);
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

