#include "types.h"

extern void Sfvwrite_130478(void);

asm void Sprint_136670(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $31, 0x8($29);
    lw         $2, 0x8($16);
    bnez       $2, L00136698;
    daddu     $2, $0, $0;
    b          L001366A8;
    sw        $0, 0x4($16);
    nop;
  L00136698:
    jal        Sfvwrite_130478;
    nop;
    sw         $0, 0x4($16);
    sw         $0, 0x8($16);
  L001366A8:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

