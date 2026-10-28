#include "types.h"

asm void sceDmaRestart_10a3e8(void)
{
    .set noreorder;
    lw         $2, 0x0($4);
    sw         $5, 0x0($4);
    srl        $2, $2, 8;
    jr         $31;
    andi      $2, $2, 0x1;
}

