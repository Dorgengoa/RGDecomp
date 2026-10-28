#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void AllocTimerCounter_1218f8(void);
extern void SetTimerHandler_122018(void);
extern void StartTimerCounter_121b90(void);

asm void SetTimerAlarm_1222f0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $22, 0x60($29);
    sd         $21, 0x50($29);
    daddu      $22, $4, $0;
    sd         $20, 0x40($29);
    daddu      $21, $6, $0;
    sd         $31, 0x70($29);
    daddu      $20, $5, $0;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    bnez       $20, L00122330;
    sd        $16, 0x0($29);
    lui        $2, (0x80000016 >> 16);
    b          L001223F4;
    ori       $2, $2, (0x80000016 & 0xFFFF);
  L00122330:
    jal        DisableIntr_120660;
    lui       $18, 0x49;
    lw         $16, -0x2980($18);
    beqz       $16, L0012234C;
    daddu     $19, $2, $0;
    lw         $2, 0x0($16);
    sw         $2, -0x2980($18);
  L0012234C:
    bnez       $16, L00122370;
    nop;
    beqz       $19, L00122364;
    nop;
    jal        EnableIntr_1206b0;
    nop;
  L00122364:
    lui        $2, (0x80008005 >> 16);
    b          L001223F4;
    ori       $2, $2, (0x80008005 & 0xFFFF);
  L00122370:
    jal        AllocTimerCounter_1218f8;
    nop;
    daddu      $17, $2, $0;
    bgezl      $17, L001223AC;
    sw        $20, 0x8($16);
    lw         $2, -0x2980($18);
    sw         $16, -0x2980($18);
    sw         $2, 0x0($16);
    sw         $0, 0x4($16);
    beqz       $19, L001223F4;
    daddu     $2, $17, $0;
    jal        EnableIntr_1206b0;
    nop;
    b          L001223F4;
    daddu     $2, $17, $0;
  L001223AC:
    lui        $6, 0x12;
    sw         $21, 0xC($16);
    addiu      $6, $6, 0x2290;
    sw         $17, 0x4($16);
    daddu      $5, $22, $0;
    daddu      $4, $17, $0;
    jal        SetTimerHandler_122018;
    daddu     $7, $16, $0;
    jal        StartTimerCounter_121b90;
    daddu     $4, $17, $0;
    beqz       $19, L001223E8;
    sll       $2, $16, 4;
    jal        EnableIntr_1206b0;
    nop;
    sll        $2, $16, 4;
  L001223E8:
    andi       $3, $17, 0xFE;
    or         $2, $2, $3;
    ori        $2, $2, 0x1;
  L001223F4:
    ld         $31, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
