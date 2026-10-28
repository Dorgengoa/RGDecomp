#include "types.h"

extern void LseekR_1309f0(void);

asm void Sseek_134530(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $7, $6, $0;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x8($29);
    daddu      $6, $5, $0;
    lw         $4, 0x54($16);
    jal        LseekR_1309f0;
    lh        $5, 0xE($16);
    addiu      $4, $0, -0x1;
    daddu      $3, $2, $0;
    dsll32     $5, $3, 0;
    dsra32     $5, $5, 0;
    bne        $3, $4, L00134578;
    lhu       $3, 0xC($16);
    b          L00134580;
    andi      $3, $3, 0xEFFF;
    nop;
  L00134578:
    sw         $5, 0x50($16);
    ori        $3, $3, 0x1000;
  L00134580:
    sh         $3, 0xC($16);
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

