#include "types.h"

extern void scePadGetDmaStr(void);

asm void scePadGetReqState(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $6, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0x10;
    lui        $2, 0x49;
    sd         $31, 0x0($29);
    addiu      $2, $2, -0x12B0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    bnez       $3, L0012BA20;
    daddu     $4, $6, $0;
    b          L0012BA2C;
    daddu     $2, $0, $0;
  L0012BA20:
    jal        scePadGetDmaStr;
    daddu     $6, $0, $0;
    lbu        $2, 0x71($2);
  L0012BA2C:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
