#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void VSync_116a30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0x1000F000 >> 16);
    addiu      $4, $0, 0x4;
    ori        $3, $3, (0x1000F000 & 0xFFFF);
    sw         $4, 0x0($3);
    sync;
    beqz       $2, L00116A68;
    lui       $3, (0x1000F000 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $3, (0x1000F000 >> 16);
  L00116A68:
    ori        $3, $3, (0x1000F000 & 0xFFFF);
    nop;
  L00116A70:
    lw         $2, 0x0($3);
    andi       $2, $2, 0x4;
    nop;
    nop;
    nop;
    beqz       $2, L00116A70;
    nop;
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0x1000F000 >> 16);
    addiu      $4, $0, 0x4;
    ori        $3, $3, (0x1000F000 & 0xFFFF);
    sw         $4, 0x0($3);
    sync;
    beqz       $2, L00116AB8;
    ld        $31, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x10;
  L00116AB8:
    jr         $31;
    addiu     $29, $29, 0x10;
}
