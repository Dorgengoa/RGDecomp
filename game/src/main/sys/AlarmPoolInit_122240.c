#include "types.h"

asm void AlarmPoolInit_122240(void)
{
    .set noreorder;
    lui        $5, 0x49;
    lui        $3, 0x49;
    addiu      $2, $5, -0x2D80;
    addiu      $4, $0, 0x3F;
    sw         $2, -0x2980($3);
    addiu      $3, $2, 0x400;
    addiu      $2, $2, 0x3F0;
    nop;
  L00122260:
    sw         $3, 0x0($2);
    addiu      $4, $4, -0x1;
    addiu      $2, $2, -0x10;
    addiu      $3, $3, -0x10;
    nop;
    bgez       $4, L00122260;
    nop;
    addiu      $3, $5, -0x2D80;
    daddu      $2, $0, $0;
    jr         $31;
    sw        $0, 0x3F0($3);
}
