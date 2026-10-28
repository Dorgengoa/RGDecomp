#include "types.h"

asm void AlarmHandlerDispatch_122290(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    andi       $4, $4, 0xFE;
    sd         $16, 0x0($29);
    daddu      $16, $7, $0;
    sd         $31, 0x10($29);
    sll        $3, $16, 4;
    or         $3, $3, $4;
    lw         $2, 0x8($16);
    lw         $7, 0xC($16);
    jalr $31, $2;
    ori       $4, $3, 0x1;
    bnez       $2, L001222E0;
    ld        $31, 0x10($29);
    lui        $3, 0x49;
    addiu      $2, $0, -0x1;
    lw         $4, -0x2980($3);
    sw         $16, -0x2980($3);
    sw         $4, 0x0($16);
    sw         $0, 0x4($16);
    ld         $31, 0x10($29);
  L001222E0:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

