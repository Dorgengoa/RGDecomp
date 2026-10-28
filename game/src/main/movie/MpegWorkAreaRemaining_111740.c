#include "types.h"

asm void MpegWorkAreaRemaining_111740(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    lw         $3, 0x4($4);
    lw         $5, 0x8($4);
    addu       $2, $2, $3;
    jr         $31;
    subu      $2, $2, $5;
}
