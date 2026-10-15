#include "types.h"
/* normal 0x00505F80 -- `jr $31 / lh $2, 0x78($4)` */
s16 normal_BtlChgPageGetScrollDir_505f80(void *p)
{
    return *(s16 *)((u8 *)p + 0x78);
}
