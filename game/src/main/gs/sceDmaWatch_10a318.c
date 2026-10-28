#include "types.h"

extern void DmaWatchAddr_109c28(void);

asm void sceDmaWatch_10a318(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $2, $0, 0x1;
    bne        $6, $2, L0010A334;
    sd        $31, 0x0($29);
    lw         $2, 0x10($4);
    b          L0010A340;
    sltu      $2, $2, $5;
  L0010A334:
    jal        DmaWatchAddr_109c28;
    daddu     $6, $7, $0;
    daddu      $2, $0, $0;
  L0010A340:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

