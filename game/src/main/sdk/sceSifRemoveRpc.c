#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceSifRemoveRpc(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    sd         $31, 0x30($29);
    jal        DisableIntr_120660;
    daddu     $17, $4, $0;
    lw         $16, 0x8($18);
    bne        $16, $17, L0011A8C8;
    nop;
    lw         $2, 0x38($16);
    b          L0011A900;
    sw        $2, 0x8($18);
  L0011A8C8:
    beqz       $16, L0011A900;
    nop;
    lw         $3, 0x38($16);
    beql       $3, $17, L0011A8FC;
    lw        $2, 0x38($17);
    nop;
  L0011A8E0:
    daddu      $16, $3, $0;
    beqz       $16, L0011A900;
    nop;
    lw         $2, 0x38($16);
    bne        $2, $17, L0011A8E0;
    daddu     $3, $2, $0;
    lw         $2, 0x38($17);
  L0011A8FC:
    sw         $2, 0x38($16);
  L0011A900:
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $16, $0;
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
