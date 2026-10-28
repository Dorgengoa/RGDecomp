#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void Timer2SetMode_120f50(void);

asm void StopTimerSystemTime_121240(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        DisableIntr_120660;
    nop;
    daddu      $16, $2, $0;
    lui        $2, (0x10001010 >> 16);
    ori        $2, $2, (0x10001010 & 0xFFFF);
    lw         $2, 0x0($2);
    andi       $3, $2, 0x80;
    bnez       $3, L00121288;
    nop;
    beqz       $16, L001212AC;
    daddu     $2, $0, $0;
    jal        EnableIntr_1206b0;
    nop;
    b          L001212AC;
    daddu     $2, $0, $0;
  L00121288:
    lui        $4, (0xFFFFF37F >> 16);
    ori        $4, $4, (0xFFFFF37F & 0xFFFF);
    jal        Timer2SetMode_120f50;
    and       $4, $2, $4;
    beqz       $16, L001212AC;
    addiu     $2, $0, 0x1;
    jal        EnableIntr_1206b0;
    nop;
    addiu      $2, $0, 0x1;
  L001212AC:
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
