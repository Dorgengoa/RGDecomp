#include "types.h"
/* normal 0x005061B0 -- increment the 0x5C counter, return 1. */
s32 normal_BtlChgPageStateIdInc_5061b0(void *p)
{
    *(s32 *)((u8 *)p + 0x5C) += 1;
    return 1;
}
