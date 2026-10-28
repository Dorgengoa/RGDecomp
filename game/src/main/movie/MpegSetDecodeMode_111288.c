#include "types.h"

asm void MpegSetDecodeMode_111288(void)
{
    .set noreorder;
    lw         $2, 0x40($4);
    sw         $7, 0xB0($2);
    sw         $5, 0xA8($2);
    jr         $31;
    sw        $6, 0xAC($2);
}
