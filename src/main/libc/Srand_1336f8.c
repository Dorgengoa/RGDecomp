#include "types.h"

asm void Srand_1336f8(void)
{
    .set noreorder;
    lui        $2, 0x45;
    dsll32     $4, $4, 0;
    lw         $3, -0x67A8($2);
    dsrl32     $4, $4, 0;
    jr         $31;
    sd        $4, 0xA8($3);
}
