#include "types.h"

extern void TimerAlarmUnlink_1214d8(void);

asm void iFreeTimerCounter_121940(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    srl        $2, $4, 10;
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    sll        $16, $2, 6;
    bltz       $4, L0012196C;
    sd        $17, 0x10($29);
    lw         $3, 0x8($16);
    andi       $2, $4, 0x3FF;
    beql       $2, $3, L00121978;
    lui       $2, 0x44;
  L0012196C:
    lui        $2, (0x80008002 >> 16);
    b          L001219CC;
    ori       $2, $2, (0x80008002 & 0xFFFF);
  L00121978:
    addiu      $17, $2, 0x78A8;
    lw         $3, 0x1C($17);
    bnel       $3, $4, L00121994;
    lw        $2, 0xC($16);
    lui        $2, (0x80000010 >> 16);
    b          L001219CC;
    ori       $2, $2, (0x80000010 & 0xFFFF);
  L00121994:
    andi       $2, $2, 0x2;
    beqz       $2, L001219A8;
    nop;
    jal        TimerAlarmUnlink_1214d8;
    daddu     $4, $16, $0;
  L001219A8:
    sw         $0, 0x8($16);
    daddu      $2, $0, $0;
    sw         $0, 0xC($16);
    lw         $4, 0x14($17);
    lw         $3, 0x10($17);
    sw         $4, 0x0($16);
    addiu      $3, $3, -0x1;
    sw         $16, 0x14($17);
    sw         $3, 0x10($17);
  L001219CC:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
