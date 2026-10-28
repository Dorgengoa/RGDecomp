#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void DmaIpuFromStart_10efb8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $5, $0;
    sd         $31, 0x20($29);
    jal        DisableIntr_120660;
    daddu     $16, $4, $0;
    daddu      $5, $2, $0;
    srl        $3, $16, 28;
    addiu      $2, $0, 0x7;
    bne        $3, $2, L0010EFFC;
    lui       $2, (0xFFFFFFF >> 16);
    lui        $3, (0x80000000 >> 16);
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    and        $16, $16, $2;
    b          L0010F004;
    or        $16, $16, $3;
  L0010EFFC:
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    and        $16, $16, $2;
  L0010F004:
    lui        $2, (0x1000B010 >> 16);
    lui        $3, (0x1000B020 >> 16);
    ori        $2, $2, (0x1000B010 & 0xFFFF);
    ori        $3, $3, (0x1000B020 & 0xFFFF);
    sw         $16, 0x0($2);
    sra        $4, $17, 4;
    sw         $4, 0x0($3);
    lui        $2, (0x1000B000 >> 16);
    ori        $2, $2, (0x1000B000 & 0xFFFF);
    addiu      $3, $0, 0x100;
    sw         $3, 0x0($2);
    beqz       $5, L0010F048;
    ld        $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x30;
  L0010F048:
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

