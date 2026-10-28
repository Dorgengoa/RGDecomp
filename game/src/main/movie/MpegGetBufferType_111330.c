#include "types.h"

asm void MpegGetBufferType_111330(void)
{
    .set noreorder;
    lw         $3, 0x40($4);
    jr         $31;
    lw        $2, 0x87C($3);
}
