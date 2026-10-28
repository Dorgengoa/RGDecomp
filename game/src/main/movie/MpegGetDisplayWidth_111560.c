#include "types.h"

asm void MpegGetDisplayWidth_111560(void)
{
    .set noreorder;
    lw         $3, 0x40($4);
    jr         $31;
    lw        $2, 0xE0($3);
}
