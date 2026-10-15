#include "types.h"
/* normal 0x005061A0 -- `jr $31 / lw $2, 0x5C($4)` */
s32 normal_BtlChgPageGetStateId_5061a0(void *p)
{
    return *(s32 *)((u8 *)p + 0x5C);
}
