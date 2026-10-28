#include "types.h"

asm void sceResetttyinit_116a20(void)
{
    .set noreorder;
    lui        $2, 0x44;
    jr         $31;
    sw        $0, 0x61F0($2);
}
