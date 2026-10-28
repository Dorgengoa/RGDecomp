#include "types.h"

asm void GetReent_12f4d0(void)
{
    .set noreorder;
    lui        $3, 0x45;
    jr         $31;
    lw        $2, -0x67A8($3);
}
