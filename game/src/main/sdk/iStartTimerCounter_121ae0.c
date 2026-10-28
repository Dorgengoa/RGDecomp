#include "types.h"

extern void iGetTimerSystemTime_1217b8(void);
extern void TimerAlarmInsertSorted_121450(void);
extern void SetNextComp_1212c0(void);

asm void iStartTimerCounter_121ae0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    srl        $2, $4, 10;
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    sll        $16, $2, 6;
    bltz       $4, L00121B0C;
    sd        $17, 0x10($29);
    lw         $3, 0x8($16);
    andi       $2, $4, 0x3FF;
    beql       $2, $3, L00121B18;
    lui       $2, 0x44;
  L00121B0C:
    lui        $2, (0x80008002 >> 16);
    b          L00121B78;
    ori       $2, $2, (0x80008002 & 0xFFFF);
  L00121B18:
    addiu      $2, $2, 0x78A8;
    lw         $3, 0x1C($2);
    bnel       $3, $4, L00121B34;
    lw        $2, 0xC($16);
    lui        $2, (0x80000010 >> 16);
    b          L00121B78;
    ori       $2, $2, (0x80000010 & 0xFFFF);
  L00121B34:
    andi       $2, $2, 0x1;
    bnez       $2, L00121B78;
    addiu     $2, $0, 0x1;
    jal        iGetTimerSystemTime_1217b8;
    nop;
    daddu      $17, $2, $0;
    lw         $2, 0xC($16);
    sd         $17, 0x10($16);
    ori        $2, $2, 0x1;
    andi       $3, $2, 0x2;
    beqz       $3, L00121B74;
    sw        $2, 0xC($16);
    jal        TimerAlarmInsertSorted_121450;
    daddu     $4, $16, $0;
    jal        SetNextComp_1212c0;
    daddu     $4, $17, $0;
  L00121B74:
    daddu      $2, $0, $0;
  L00121B78:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
