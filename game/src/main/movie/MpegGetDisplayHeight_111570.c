#include "types.h"

asm void MpegGetDisplayHeight_111570(void)
{
    .set noreorder;
    lw         $3, 0x40($4);
    jr         $31;
    lw        $2, 0xE4($3);
}
