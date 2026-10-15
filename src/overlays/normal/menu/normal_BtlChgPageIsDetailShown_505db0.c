#include "types.h"
/* normal 0x00505DB0 -- leaf signed-byte accessor, +0x70 (`lb`). */

typedef struct Ctx { u8 pad000[0x70]; s8 f070; } Ctx;

s32 normal_BtlChgPageIsDetailShown_505db0(Ctx *p)
{
    return p->f070;
}
