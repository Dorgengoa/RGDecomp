#include "types.h"

asm void MpegIsRefBuffEmpty_111278(void)
{
    .set noreorder;
    lw         $3, 0x40($4);
    lw         $2, 0x4($3);
    jr         $31;
    sltiu     $2, $2, 0x1;
}
