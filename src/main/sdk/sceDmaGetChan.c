#include "types.h"

asm void *sceDmaGetChan(s32 id)
{
    .set noreorder;
    sltiu      $2, $4, 0xA;
    beqz       $2, L00109D30;
    lui       $2, 0x44;
    sll        $3, $4, 2;
    addiu      $2, $2, 0x5F20;
    addu       $3, $3, $2;
    jr         $31;
    lw        $2, 0x0($3);
  L00109D30:
    jr         $31;
    daddu     $2, $0, $0;
}
