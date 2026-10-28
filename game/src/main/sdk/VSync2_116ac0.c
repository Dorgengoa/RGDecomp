#include "types.h"

extern void SetVSyncFlag(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void VSync2_116ac0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    daddu      $4, $29, $0;
    sw         $0, 0x0($29);
    jal        SetVSyncFlag;
    ori       $5, $29, 0x8;
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0x1000F000 >> 16);
    addiu      $4, $0, 0x4;
    ori        $3, $3, (0x1000F000 & 0xFFFF);
    sw         $4, 0x0($3);
    sync;
    beqz       $2, L00116B08;
    lui       $3, (0x1000F000 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $3, (0x1000F000 >> 16);
  L00116B08:
    ori        $3, $3, (0x1000F000 & 0xFFFF);
    nop;
  L00116B10:
    lw         $2, 0x0($3);
    andi       $2, $2, 0x4;
    bnez       $2, L00116B2C;
    nop;
    lw         $2, 0x0($29);
    beqz       $2, L00116B10;
    nop;
  L00116B2C:
    jal        DisableIntr_120660;
    nop;
    addiu      $3, $0, 0x4;
    lui        $1, (0x10010000 >> 16);
    sw         $3, -0x1000($1);
    sync;
    beqz       $2, L00116B54;
    nop;
    jal        EnableIntr_1206b0;
    nop;
  L00116B54:
    ld         $2, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
