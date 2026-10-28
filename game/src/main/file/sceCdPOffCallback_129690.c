#include "types.h"

extern void PowerOffCB_129768(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceCdPOffCallback_129690(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $2, 0x44;
    sd         $18, 0x20($29);
    sd         $16, 0x0($29);
    daddu      $18, $4, $0;
    lw         $3, 0x7988($2);
    daddu      $16, $5, $0;
    sd         $31, 0x30($29);
    bgez       $3, L001296C0;
    sd        $17, 0x10($29);
    jal        PowerOffCB_129768;
    nop;
  L001296C0:
    jal        DisableIntr_120660;
    nop;
    lui        $5, 0x49;
    lui        $4, 0x49;
    lw         $17, -0x15B8($5);
    lui        $3, 0x49;
    sw         $16, -0x15B0($4);
    sw         $18, -0x15B8($5);
    sw         $28, -0x15B4($3);
    beqz       $2, L001296F8;
    daddu     $2, $17, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $17, $0;
  L001296F8:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
