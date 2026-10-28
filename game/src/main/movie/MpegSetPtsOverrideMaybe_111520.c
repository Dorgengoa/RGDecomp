#include "types.h"

asm void MpegSetPtsOverrideMaybe_111520(void)
{
    .set noreorder;
    lw         $3, 0x40($4);
    addiu      $2, $0, 0x1;
    addiu      $4, $0, 0x1;
    sd         $5, 0x90($3);
    jr         $31;
    sw        $4, 0x8C($3);
}
