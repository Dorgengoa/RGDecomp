#include "types.h"

extern void DisableIntr_120660(void);
extern void iAllocTimerCounter_121888(void);
extern void EnableIntr_1206b0(void);

asm void AllocTimerCounter_1218f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    nop;
    jal        iAllocTimerCounter_121888;
    daddu     $16, $2, $0;
    beqz       $16, L00121928;
    daddu     $17, $2, $0;
    jal        EnableIntr_1206b0;
    nop;
  L00121928:
    daddu      $2, $17, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
