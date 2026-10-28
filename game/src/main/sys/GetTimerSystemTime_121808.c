#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void GetTimerSystemTime_121808(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0x10001000 >> 16);
    lui        $4, 0x44;
    ori        $3, $3, (0x10001000 & 0xFFFF);
    lwu        $16, 0x0($3);
    lw         $8, 0x10($3);
    ld         $10, 0x78A8($4);
    andi       $9, $8, 0x800;
    beqz       $9, L00121848;
    addiu     $9, $0, 0x2;
    lwu        $16, 0x0($3);
    daddiu     $10, $10, 0x1;
  L00121848:
    andi       $8, $8, 0x3;
    dsll       $10, $10, 16;
    movz       $9, $0, $8;
    or         $16, $16, $10;
    dsllv      $9, $9, $8;
    dsllv      $16, $16, $9;
    beqz       $2, L00121874;
    daddu     $2, $16, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $16, $0;
  L00121874:
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
