#include "types.h"

asm void sceSifCheckStatRpc(void)
{
    .set noreorder;
    lw         $5, 0x0($4);
    beqz       $5, L0011A714;
    nop;
    lw         $3, 0x4($4);
    lw         $2, 0x18($5);
    bne        $3, $2, L0011A714;
    nop;
    lw         $2, 0x10($5);
    andi       $2, $2, 0x1;
    bnez       $2, L0011A71C;
    nop;
  L0011A714:
    jr         $31;
    daddu     $2, $0, $0;
  L0011A71C:
    jr         $31;
    addiu     $2, $0, 0x1;
}
