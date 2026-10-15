#include "types.h"

extern void StreamChanStart_1d6d00(u8 *p, void *a, void *b);

void StreamMgrStartChan_1d66f0(u8 *base, s32 i, void *a, void *b)
{
    if (i < 0 || i >= 4) return;
    StreamChanStart_1d6d00(base + i * 224, a, b);
}
