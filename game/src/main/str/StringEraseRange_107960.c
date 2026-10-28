#include "types.h"

extern void StringReplace_106f90(void);

asm void StringEraseRange_107960(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $6, $0;
    lw         $2, 0x0($5);
    daddu      $16, $4, $0;
    andi       $2, $2, 0x1;
    beqz       $2, L00107990;
    subu      $6, $7, $6;
    b          L00107994;
    lw        $3, 0x8($5);
  L00107990:
    addiu      $3, $5, 0x1;
  L00107994:
    dsll32     $2, $17, 0;
    lb         $9, 0x3C($29);
    dsra32     $2, $2, 0;
    daddu      $4, $5, $0;
    subu       $5, $2, $3;
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

