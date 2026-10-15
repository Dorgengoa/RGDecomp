#include "types.h"

extern void StreamChanSetVolumeFade_1d6f90(u8 *p, void *a);

void StreamMgrSetChanVolumeFade_1d63a0(u8 *base, s32 i, void *a)
{
    if (i < 0 || i >= 4) return;
    StreamChanSetVolumeFade_1d6f90(base + i * 224, a);
}
