#include "types.h"
/* normal 0x00505FB0 -- `jr $31 / lb $2, 0x72($4)` */
s8 normal_BtlChgPageGetCloseCode_505fb0(void *p)
{
    return *(s8 *)((u8 *)p + 0x72);
}
