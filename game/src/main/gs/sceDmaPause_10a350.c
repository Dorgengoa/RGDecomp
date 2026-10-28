#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void sceDmaPause_10a350(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    daddu      $17, $4, $0;
    jal        DisableIntr_120660;
    sd        $16, 0x0($29);
    daddu      $7, $2, $0;
    lui        $4, (0x10000 >> 16);
    lui        $2, (0x1000F520 >> 16);
    ori        $2, $2, (0x1000F520 & 0xFFFF);
    lw         $6, 0x0($2);
    and        $3, $6, $4;
    bnez       $3, L0010A398;
    lui       $2, (0x1000F590 >> 16);
    or         $3, $6, $4;
    ori        $2, $2, (0x1000F590 & 0xFFFF);
    sw         $3, 0x0($2);
    lui        $2, (0x1000E000 >> 16);
  L0010A398:
    lui        $4, (0xFFFFFEFF >> 16);
    ori        $2, $2, (0x1000E000 & 0xFFFF);
    ori        $4, $4, (0xFFFFFEFF & 0xFFFF);
    lw         $5, 0x0($2);
    lui        $3, (0x1000F590 >> 16);
    lw         $16, 0x0($17);
    ori        $3, $3, (0x1000F590 & 0xFFFF);
    and        $4, $16, $4;
    sw         $4, 0x0($17);
    sw         $6, 0x0($3);
    beqz       $7, L0010A3D4;
    daddu     $2, $16, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $16, $0;
  L0010A3D4:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

