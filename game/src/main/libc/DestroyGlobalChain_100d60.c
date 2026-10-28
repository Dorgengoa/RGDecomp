#include "types.h"

asm void DestroyGlobalChain_100d60(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $3, 0x48;
    sd         $31, 0x0($29);
    lw         $6, 0x53D0($3);
    beqz       $6, L00100DA8;
    nop;
    lw         $3, 0x0($6);
  L00100D7C:
    lui        $2, 0x48;
    sw         $3, 0x53D0($2);
    lw         $4, 0x8($6);
    lw         $2, 0x4($6);
    jalr $31, $2;
    addiu     $5, $0, -0x1;
    lui        $3, 0x48;
    lw         $6, 0x53D0($3);
    bnel       $6, $0, L00100D7C;
    lw        $3, 0x0($6);
    nop;
  L00100DA8:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

