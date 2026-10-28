#include "types.h"

extern void DisableIntr_120660(void);
extern void iSetTimerHandler_121f20(void);
extern void EnableIntr_1206b0(void);

asm void SetTimerHandler_122018(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    daddu      $19, $7, $0;
    sd         $17, 0x10($29);
    daddu      $18, $6, $0;
    sd         $16, 0x0($29);
    daddu      $17, $5, $0;
    sd         $20, 0x40($29);
    sd         $31, 0x50($29);
    jal        DisableIntr_120660;
    daddu     $16, $4, $0;
    daddu      $4, $16, $0;
    daddu      $20, $2, $0;
    daddu      $5, $17, $0;
    daddu      $6, $18, $0;
    jal        iSetTimerHandler_121f20;
    daddu     $7, $19, $0;
    beqz       $20, L00122070;
    daddu     $16, $2, $0;
    jal        EnableIntr_1206b0;
    nop;
  L00122070:
    daddu      $2, $16, $0;
    ld         $31, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
