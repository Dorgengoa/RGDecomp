#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceSifRemoveRpcQueue(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    daddu     $17, $4, $0;
    lui        $3, 0x49;
    addiu      $3, $3, -0x7CC0;
    lw         $16, 0x28($3);
    bne        $16, $17, L0011A960;
    nop;
    lw         $2, 0x14($16);
    b          L0011A998;
    sw        $2, 0x28($3);
  L0011A960:
    beqz       $16, L0011A998;
    nop;
    lw         $3, 0x14($16);
    beql       $3, $17, L0011A994;
    lw        $2, 0x14($17);
    nop;
  L0011A978:
    daddu      $16, $3, $0;
    beqz       $16, L0011A998;
    nop;
    lw         $2, 0x14($16);
    bne        $2, $17, L0011A978;
    daddu     $3, $2, $0;
    lw         $2, 0x14($17);
  L0011A994:
    sw         $2, 0x14($16);
  L0011A998:
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $16, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
