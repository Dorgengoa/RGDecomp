#include "types.h"

typedef rg_u128 u128;

asm void sceVu0CopyVector(u128 *dst, const u128 *src, s32 unused)
{
    .set noreorder;
    lq         $6, 0x0($5);
    jr         $31;
    sq        $6, 0x0($4);
}
