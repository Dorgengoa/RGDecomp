#include "types.h"

asm void sceCdPoffIntr_129710(void)
{
    .set noreorder;
    lui        $2, 0x49;
    addiu      $29, $29, -0x20;
    lw         $5, -0x15B8($2);
    sd         $31, 0x10($29);
    beqz       $5, L00129754;
    sd        $16, 0x0($29);
    lui        $2, 0x44;
    lw         $3, 0x7964($2);
    bnez       $3, L00129758;
    ld        $31, 0x10($29);
    lui        $2, 0x49;
    daddu      $16, $28, $0;
    lw         $28, -0x15B4($2);
    lui        $3, 0x49;
    jalr $31, $5;
    lw        $4, -0x15B0($3);
    daddu      $28, $16, $0;
  L00129754:
    ld         $31, 0x10($29);
  L00129758:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

