#include "types.h"

asm void KernelVblankResetRelated_446d00(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, (0x1000F000 >> 16);
    sd         $31, 0x0($29);
    addiu      $3, $0, 0x4;
    ori        $2, $2, (0x1000F000 & 0xFFFF);
    lui        $4, (0x1000F000 >> 16);
    sw         $3, 0x0($2);
    ori        $4, $4, (0x1000F000 & 0xFFFF);
  L00446D20:
    lw         $2, 0x0($4);
    andi       $2, $2, 0x4;
    nop;
    nop;
    nop;
    beqz       $2, L00446D20;
    nop;
    lui        $2, (0x1000F000 >> 16);
    addiu      $4, $0, 0x4;
    ori        $2, $2, (0x1000F000 & 0xFFFF);
    lui        $3, 0x8007;
    sw         $4, 0x0($2);
    lw         $2, (0x80074760 & 0xFFFF)($3);
    jalr       $31, $2;
    nop;
    lui        $2, 0x8007;
    addiu      $5, $0, 0x2;
    lw         $3, (0x80074764 & 0xFFFF)($2);
    addiu      $6, $0, 0x1;
    jalr       $31, $3;
    addiu      $4, $0, 0x1;
    lui        $2, 0x8007;
    lw         $3, (0x8007474C & 0xFFFF)($2);
    jalr       $31, $3;
    ori        $4, $0, 0xDFFD;
    lui        $2, 0x8007;
    lw         $3, (0x80074750 & 0xFFFF)($2);
    jalr       $31, $3;
    nop;
    lui        $2, 0x8007;
    lw         $3, (0x8007475C & 0xFFFF)($2);
    jalr       $31, $3;
    addiu      $4, $0, 0x7F;
    lui        $2, 0x8007;
    lw         $3, (0x80074754 & 0xFFFF)($2);
    jalr       $31, $3;
    nop;
    lui        $2, 0x8007;
    lw         $3, (0x80074758 & 0xFFFF)($2);
    jalr       $31, $3;
    nop;
    ld         $31, 0x0($29);
    jr         $31;
    addiu      $29, $29, 0x10;
}
