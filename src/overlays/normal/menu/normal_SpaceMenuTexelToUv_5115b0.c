#include "types.h"
/* normal 0x005115B0 -- `sll $2,$4,4 / addiu $2,$2,8`. */

s32 normal_SpaceMenuTexelToUv_5115b0(s32 i)
{
    return (i * 16) + 8;
}
