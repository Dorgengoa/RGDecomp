#include "types.h"

extern void iGetTimerSystemTime_1217b8(void);
extern void TimerAlarmUnlink_1214d8(void);
extern void SetNextComp_1212c0(void);

asm void iStopTimerCounter_121be0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    srl        $2, $4, 10;
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    sll        $16, $2, 6;
    bltz       $4, L00121C0C;
    sd        $17, 0x10($29);
    lw         $3, 0x8($16);
    andi       $2, $4, 0x3FF;
    beql       $2, $3, L00121C18;
    lui       $2, 0x44;
  L00121C0C:
    lui        $2, (0x80008002 >> 16);
    b          L00121C90;
    ori       $2, $2, (0x80008002 & 0xFFFF);
  L00121C18:
    addiu      $2, $2, 0x78A8;
    lw         $3, 0x1C($2);
    bnel       $3, $4, L00121C34;
    lw        $2, 0xC($16);
    lui        $2, (0x80000010 >> 16);
    b          L00121C90;
    ori       $2, $2, (0x80000010 & 0xFFFF);
  L00121C34:
    andi       $2, $2, 0x1;
    beqz       $2, L00121C90;
    daddu     $2, $0, $0;
    jal        iGetTimerSystemTime_1217b8;
    nop;
    lw         $5, 0xC($16);
    daddu      $17, $2, $0;
    ld         $4, 0x10($16);
    lui        $2, (0xFFFFFFFE >> 16);
    ld         $3, 0x18($16);
    ori        $2, $2, (0xFFFFFFFE & 0xFFFF);
    dsubu      $4, $17, $4;
    andi       $6, $5, 0x2;
    daddu      $3, $3, $4;
    and        $5, $5, $2;
    sd         $3, 0x18($16);
    beqz       $6, L00121C8C;
    sw        $5, 0xC($16);
    jal        TimerAlarmUnlink_1214d8;
    daddu     $4, $16, $0;
    jal        SetNextComp_1212c0;
    daddu     $4, $17, $0;
  L00121C8C:
    addiu      $2, $0, 0x1;
  L00121C90:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
