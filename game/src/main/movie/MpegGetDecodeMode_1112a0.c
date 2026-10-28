#include "types.h"

asm void MpegGetDecodeMode_1112a0(void)
{
    .set noreorder;
    lw         $8, 0x40($4);
    lw         $2, 0xA8($8);
    sw         $2, 0x0($5);
    lw         $3, 0xAC($8);
    sw         $3, 0x0($6);
    lw         $2, 0xB0($8);
    jr         $31;
    sw        $2, 0x0($7);
}
