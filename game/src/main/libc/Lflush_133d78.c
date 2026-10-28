#include "types.h"

extern void Fflush_12f590(void);

asm void Lflush_133d78(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $3, $0, 0x9;
    sd         $31, 0x0($29);
    lhu        $2, 0xC($4);
    andi       $2, $2, 0x9;
    bne        $2, $3, L00133DA0;
    ld        $31, 0x0($29);
    j          Fflush_12f590;
    addiu     $29, $29, 0x10;
    nop;
  L00133DA0:
    daddu      $2, $0, $0;
    jr         $31;
    addiu     $29, $29, 0x10;
}
