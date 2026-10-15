#include "types.h"

asm void iGetTimerUsedUnitNum_121a30(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $3, $2, 0x78A8;
    lw         $2, 0x8($3);
    bgez       $2, L00121A50;
    nop;
    lui        $2, (0x80008001 >> 16);
    jr         $31;
    ori       $2, $2, (0x80008001 & 0xFFFF);
  L00121A50:
    beqz       $4, L00121A60;
    nop;
    lw         $2, 0x10($3);
    sw         $2, 0x0($4);
  L00121A60:
    beqz       $5, L00121A78;
    nop;
    lw         $3, 0x10($3);
    addiu      $2, $0, 0x80;
    subu       $2, $2, $3;
    sw         $2, 0x0($5);
  L00121A78:
    jr         $31;
    daddu     $2, $0, $0;
}
