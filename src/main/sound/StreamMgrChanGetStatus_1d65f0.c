#include "types.h"

extern s32 StreamChanGetStatus_1d6bb0(u8 *p);

s32 StreamMgrChanGetStatus_1d65f0(u8 *base, s32 i)
{
    if (i < 0) goto fail;
    if (i < 4) goto ok;
fail:
    return -2;
ok:
    return StreamChanGetStatus_1d6bb0(base + i * 224);
}
