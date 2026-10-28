#include "types.h"

extern void iAllocTimerCounter_121888(void);
extern void iSetTimerHandler_121f20(void);
extern void iStartTimerCounter_121ae0(void);

asm void iSetTimerAlarm_122420(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    daddu      $21, $4, $0;
    sd         $19, 0x30($29);
    daddu      $20, $6, $0;
    sd         $31, 0x60($29);
    daddu      $19, $5, $0;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    bnez       $19, L0012245C;
    sd        $16, 0x0($29);
    lui        $2, (0x80000016 >> 16);
    b          L001224EC;
    ori       $2, $2, (0x80000016 & 0xFFFF);
  L0012245C:
    lui        $18, 0x49;
    lw         $16, -0x2980($18);
    beqz       $16, L00122474;
    nop;
    lw         $2, 0x0($16);
    sw         $2, -0x2980($18);
  L00122474:
    bnez       $16, L00122488;
    nop;
    lui        $2, (0x80008005 >> 16);
    b          L001224EC;
    ori       $2, $2, (0x80008005 & 0xFFFF);
  L00122488:
    jal        iAllocTimerCounter_121888;
    nop;
    daddu      $17, $2, $0;
    bgezl      $17, L001224B4;
    sw        $19, 0x8($16);
    lw         $3, -0x2980($18);
    sw         $16, -0x2980($18);
    sw         $3, 0x0($16);
    sw         $0, 0x4($16);
    b          L001224F0;
    ld        $31, 0x60($29);
  L001224B4:
    lui        $6, 0x12;
    sw         $20, 0xC($16);
    addiu      $6, $6, 0x2290;
    sw         $17, 0x4($16);
    daddu      $5, $21, $0;
    daddu      $4, $17, $0;
    jal        iSetTimerHandler_121f20;
    daddu     $7, $16, $0;
    jal        iStartTimerCounter_121ae0;
    daddu     $4, $17, $0;
    sll        $2, $16, 4;
    andi       $3, $17, 0xFE;
    or         $2, $2, $3;
    ori        $2, $2, 0x1;
  L001224EC:
    ld         $31, 0x60($29);
  L001224F0:
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}
