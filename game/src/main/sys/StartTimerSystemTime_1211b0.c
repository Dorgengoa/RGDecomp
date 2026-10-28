#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void Timer2SetMode_120f50(void);
extern void iGetTimerSystemTime_1217b8(void);
extern void SetNextComp_1212c0(void);

asm void StartTimerSystemTime_1211b0(void)
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
    beqz       $3, L001211F8;
    nop;
    beqz       $16, L00121230;
    addiu     $2, $0, 0x1;
    jal        EnableIntr_1206b0;
    nop;
    b          L00121230;
    addiu     $2, $0, 0x1;
  L001211F8:
    lui        $4, (0xFFFFF3FF >> 16);
    ori        $4, $4, (0xFFFFF3FF & 0xFFFF);
    and        $4, $2, $4;
    jal        Timer2SetMode_120f50;
    ori       $4, $4, 0x80;
    jal        iGetTimerSystemTime_1217b8;
    nop;
    jal        SetNextComp_1212c0;
    daddu     $4, $2, $0;
    beqz       $16, L00121230;
    daddu     $2, $0, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $0, $0;
  L00121230:
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
