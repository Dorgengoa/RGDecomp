#include "types.h"

extern void Sfvwrite_130478(void);

asm void Sprint_1373e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $31, 0x8($29);
    lw         $2, 0x8($16);
    bnez       $2, L00137408;
    daddu     $2, $0, $0;
    b          L00137418;
    sw        $0, 0x4($16);
    nop;
  L00137408:
    jal        Sfvwrite_130478;
    nop;
    sw         $0, 0x4($16);
    sw         $0, 0x8($16);
  L00137418:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

