#include "types.h"

/* Member of the 9-clone group headed by StreamMgrSetChanGain_1d63f0 (64 B each).
   This member differs from the head in the worker called.  The reading is
   written up in StreamMgrSetChanGain_1d63f0.c. */

extern void StreamChanPlay_1d6c30(void *rec);

void StreamMgrPlayChan_1d6670(void *base, s32 i)
{
    if (i < 0 || i >= 4) {
        return;
    }
    StreamChanPlay_1d6c30((u8 *)base + i * 224);
}
