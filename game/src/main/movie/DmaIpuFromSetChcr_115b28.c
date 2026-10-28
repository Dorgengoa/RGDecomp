#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void DmaIpuFromSetChcr_115b28(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        DisableIntr_120660;
    daddu     $16, $4, $0;
    lui        $6, (0x1000F520 >> 16);
    lui        $7, (0x1000F590 >> 16);
    ori        $6, $6, (0x1000F520 & 0xFFFF);
    lui        $8, (0x10000 >> 16);
    lw         $3, 0x0($6);
    ori        $7, $7, (0x1000F590 & 0xFFFF);
    lui        $4, (0x1000B000 >> 16);
    lui        $5, (0xFFFEFFFF >> 16);
    or         $3, $3, $8;
    ori        $4, $4, (0x1000B000 & 0xFFFF);
    sw         $3, 0x0($7);
    ori        $5, $5, (0xFFFEFFFF & 0xFFFF);
    sw         $16, 0x0($4);
    lw         $3, 0x0($6);
    and        $3, $3, $5;
    sw         $3, 0x0($7);
    beqz       $2, L00115B90;
    ld        $31, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x20;
  L00115B90:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
