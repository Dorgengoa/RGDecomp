#include "types.h"

extern void TimerAlarmUnlink_1214d8(void);
extern void TimerAlarmInsertSorted_121450(void);
extern void iGetTimerSystemTime_1217b8(void);
extern void SetNextComp_1212c0(void);

asm void iSetTimerHandler_121f20(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    srl        $2, $4, 10;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    daddu      $19, $7, $0;
    sd         $17, 0x10($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    daddu      $17, $6, $0;
    sd         $31, 0x40($29);
    bltz       $4, L00121F60;
    sll       $16, $2, 6;
    lw         $3, 0x8($16);
    andi       $2, $4, 0x3FF;
    beql       $2, $3, L00121F6C;
    lui       $2, 0x44;
  L00121F60:
    lui        $2, (0x80008002 >> 16);
    b          L00121FF8;
    ori       $2, $2, (0x80008002 & 0xFFFF);
  L00121F6C:
    addiu      $2, $2, 0x78A8;
    lw         $3, 0x1C($2);
    bnel       $3, $4, L00121F88;
    lw        $3, 0xC($16);
    lui        $2, (0x80000010 >> 16);
    b          L00121FF8;
    ori       $2, $2, (0x80000010 & 0xFFFF);
  L00121F88:
    andi       $2, $3, 0x2;
    beqz       $2, L00121FA0;
    nop;
    jal        TimerAlarmUnlink_1214d8;
    daddu     $4, $16, $0;
    lw         $3, 0xC($16);
  L00121FA0:
    bnez       $17, L00121FBC;
    sw        $17, 0x28($16);
    lui        $2, (0xFFFFFFFD >> 16);
    ori        $2, $2, (0xFFFFFFFD & 0xFFFF);
    and        $2, $3, $2;
    b          L00121FE4;
    sw        $2, 0xC($16);
  L00121FBC:
    ori        $2, $3, 0x2;
    sd         $18, 0x20($16);
    sw         $2, 0xC($16);
    sw         $28, 0x2C($16);
    lw         $2, 0xC($16);
    andi       $2, $2, 0x1;
    beqz       $2, L00121FE4;
    sw        $19, 0x30($16);
    jal        TimerAlarmInsertSorted_121450;
    daddu     $4, $16, $0;
  L00121FE4:
    jal        iGetTimerSystemTime_1217b8;
    nop;
    jal        SetNextComp_1212c0;
    daddu     $4, $2, $0;
    daddu      $2, $0, $0;
  L00121FF8:
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
