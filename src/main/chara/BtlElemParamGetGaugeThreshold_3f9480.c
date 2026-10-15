#include "types.h"
s32 BtlElemParamGetGaugeThreshold_3f9480(u8 *p, s32 i)
{
    /* `slti $1` = the $at compare class: `i > 3`, not `i >= 4`. */
    if (i <= 0 || i > 3) return -1;
    return *(s8 *)(i + (s32)p + 0xC9);
}
