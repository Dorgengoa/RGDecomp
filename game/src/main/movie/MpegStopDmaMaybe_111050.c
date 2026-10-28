#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void IpuInit_115f30(void);

asm void MpegStopDmaMaybe_111050(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        DisableIntr_120660;
    nop;
    lui        $9, (0x1000F520 >> 16);
    lui        $4, (0x10000 >> 16);
    ori        $9, $9, (0x1000F520 & 0xFFFF);
    lui        $10, (0x1000F590 >> 16);
    lw         $3, 0x0($9);
    ori        $10, $10, (0x1000F590 & 0xFFFF);
    lui        $6, (0x1000B000 >> 16);
    lui        $8, (0xFFFFFEFF >> 16);
    or         $3, $3, $4;
    ori        $6, $6, (0x1000B000 & 0xFFFF);
    sw         $3, 0x0($10);
    ori        $8, $8, (0xFFFFFEFF & 0xFFFF);
    lui        $5, (0x1000B400 >> 16);
    lui        $7, (0xFFFEFFFF >> 16);
    lw         $4, 0x0($6);
    ori        $5, $5, (0x1000B400 & 0xFFFF);
    ori        $7, $7, (0xFFFEFFFF & 0xFFFF);
    and        $4, $4, $8;
    sw         $4, 0x0($6);
    lw         $3, 0x0($5);
    and        $3, $3, $8;
    sw         $3, 0x0($5);
    lw         $4, 0x0($9);
    and        $4, $4, $7;
    sw         $4, 0x0($10);
    beqz       $2, L001110D8;
    lui       $2, (0x1000B020 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $2, (0x1000B020 >> 16);
  L001110D8:
    lui        $3, (0x1000B420 >> 16);
    ori        $2, $2, (0x1000B020 & 0xFFFF);
    ori        $3, $3, (0x1000B420 & 0xFFFF);
    sw         $0, 0x0($2);
    jal        IpuInit_115f30;
    sw        $0, 0x0($3);
    ld         $31, 0x0($29);
    addiu      $2, $0, 0x1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
