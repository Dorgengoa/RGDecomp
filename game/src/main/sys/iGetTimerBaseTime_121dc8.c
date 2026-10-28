#include "types.h"

asm void iGetTimerBaseTime_121dc8(void)
{
    .set noreorder;
    srl        $2, $4, 10;
    bltz       $4, L00121DE4;
    sll       $5, $2, 6;
    lw         $3, 0x8($5);
    andi       $2, $4, 0x3FF;
    beql       $2, $3, L00121DEC;
    lw        $2, 0xC($5);
  L00121DE4:
    jr         $31;
    addiu     $2, $0, -0x1;
  L00121DEC:
    andi       $2, $2, 0x1;
    beqz       $2, L00121E08;
    nop;
    ld         $3, 0x18($5);
    ld         $2, 0x10($5);
    jr         $31;
    dsubu     $2, $2, $3;
  L00121E08:
    jr         $31;
    daddu     $2, $0, $0;
}
