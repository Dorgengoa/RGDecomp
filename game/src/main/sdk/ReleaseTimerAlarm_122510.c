#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void FreeTimerCounter_1219e0(void);

asm void ReleaseTimerAlarm_122510(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x10($29);
    srl        $2, $16, 8;
    sd         $18, 0x20($29);
    sd         $31, 0x30($29);
    jal        DisableIntr_120660;
    sll       $17, $2, 4;
    bltz       $16, L00122550;
    daddu     $18, $2, $0;
    lw         $2, 0x4($17);
    xor        $2, $16, $2;
    andi       $2, $2, 0xFF;
    beqz       $2, L0012256C;
    nop;
  L00122550:
    beqz       $18, L00122560;
    nop;
    jal        EnableIntr_1206b0;
    nop;
  L00122560:
    lui        $2, (0x80008002 >> 16);
    b          L001225A0;
    ori       $2, $2, (0x80008002 & 0xFFFF);
  L0012256C:
    lw         $4, 0x4($17);
    jal        FreeTimerCounter_1219e0;
    nop;
    lui        $3, 0x49;
    lw         $2, -0x2980($3);
    sw         $17, -0x2980($3);
    sw         $2, 0x0($17);
    sw         $0, 0x4($17);
    beqz       $18, L001225A0;
    daddu     $2, $0, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $0, $0;
  L001225A0:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
