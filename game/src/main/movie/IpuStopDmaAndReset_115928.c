#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void IpuStopDmaAndReset_115928(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        DisableIntr_120660;
    nop;
    lui        $7, (0x1000F520 >> 16);
    lui        $4, (0x10000 >> 16);
    ori        $7, $7, (0x1000F520 & 0xFFFF);
    lui        $8, (0x1000F590 >> 16);
    lw         $3, 0x0($7);
    ori        $8, $8, (0x1000F590 & 0xFFFF);
    lui        $5, (0x1000B000 >> 16);
    lui        $6, (0x1000B400 >> 16);
    or         $3, $3, $4;
    ori        $5, $5, (0x1000B000 & 0xFFFF);
    sw         $3, 0x0($8);
    ori        $6, $6, (0x1000B400 & 0xFFFF);
    sw         $0, 0x0($5);
    lui        $4, (0xFFFEFFFF >> 16);
    sw         $0, 0x0($6);
    ori        $4, $4, (0xFFFEFFFF & 0xFFFF);
    lw         $3, 0x0($7);
    and        $3, $3, $4;
    sw         $3, 0x0($8);
    beqz       $2, L00115998;
    lui       $2, (0x1000B020 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $2, (0x1000B020 >> 16);
  L00115998:
    lui        $4, (0x1000B420 >> 16);
    ori        $2, $2, (0x1000B020 & 0xFFFF);
    ori        $4, $4, (0x1000B420 & 0xFFFF);
    sw         $0, 0x0($2);
    lui        $3, (0x10002010 >> 16);
    sw         $0, 0x0($4);
    ori        $3, $3, (0x10002010 & 0xFFFF);
    lui        $2, (0x40000000 >> 16);
    ld         $31, 0x0($29);
    sw         $2, 0x0($3);
    jr         $31;
    addiu     $29, $29, 0x10;
}
