#include "types.h"

extern void iFreeTimerCounter_121940(void);

asm void iReleaseTimerAlarm_1225b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    srl        $2, $4, 8;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    bltz       $4, L001225E4;
    sll       $16, $2, 4;
    lw         $2, 0x4($16);
    xor        $2, $4, $2;
    andi       $2, $2, 0xFF;
    beqz       $2, L001225F0;
    nop;
  L001225E4:
    lui        $2, (0x80008002 >> 16);
    b          L00122620;
    ori       $2, $2, (0x80008002 & 0xFFFF);
  L001225F0:
    lw         $4, 0x4($16);
    jal        iFreeTimerCounter_121940;
    nop;
    daddu      $4, $2, $0;
    bnez       $4, L00122620;
    daddu     $2, $4, $0;
    lui        $2, 0x49;
    lw         $3, -0x2980($2);
    sw         $16, -0x2980($2);
    sw         $3, 0x0($16);
    sw         $0, 0x4($16);
    daddu      $2, $4, $0;
  L00122620:
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
