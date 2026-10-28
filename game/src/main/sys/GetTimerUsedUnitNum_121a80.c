#include "types.h"

extern void DisableIntr_120660(void);
extern void iGetTimerUsedUnitNum_121a30(void);
extern void EnableIntr_1206b0(void);

asm void GetTimerUsedUnitNum_121a80(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $5, $0;
    sd         $18, 0x20($29);
    sd         $31, 0x30($29);
    jal        DisableIntr_120660;
    daddu     $16, $4, $0;
    daddu      $4, $16, $0;
    daddu      $18, $2, $0;
    jal        iGetTimerUsedUnitNum_121a30;
    daddu     $5, $17, $0;
    beqz       $18, L00121AC0;
    daddu     $16, $2, $0;
    jal        EnableIntr_1206b0;
    nop;
  L00121AC0:
    daddu      $2, $16, $0;
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
