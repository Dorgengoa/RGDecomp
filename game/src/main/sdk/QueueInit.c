#include "types.h"

asm void QueueInit(void)
{
    .set noreorder;
    lui        $2, 0x48;
    addiu      $3, $2, 0x6400;
    sw         $4, 0x6400($2);
    addiu      $4, $3, 0x10;
    daddu      $2, $3, $0;
    sw         $4, 0x8($3);
    sw         $0, 0x4($3);
    jr         $31;
    sw        $4, 0xC($3);
}
