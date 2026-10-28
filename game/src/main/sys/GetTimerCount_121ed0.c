#include "types.h"

extern void DisableIntr_120660(void);
extern void iGetTimerCount_121e60(void);
extern void EnableIntr_1206b0(void);

asm void GetTimerCount_121ed0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    daddu     $16, $4, $0;
    daddu      $4, $16, $0;
    jal        iGetTimerCount_121e60;
    daddu     $17, $2, $0;
    beqz       $17, L00121F04;
    daddu     $16, $2, $0;
    jal        EnableIntr_1206b0;
    nop;
  L00121F04:
    daddu      $2, $16, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
