#include "types.h"

asm void MpegSetNextPtsMaybe_1115b0(void)
{
    .set noreorder;
    lw         $6, 0x40($4);
    addiu      $3, $0, 0x1;
    addiu      $2, $0, 0x1;
    sw         $3, 0x108($6);
    jr         $31;
    sd        $5, 0x100($6);
}
