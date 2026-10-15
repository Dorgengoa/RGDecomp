#include "types.h"

/* Member of the 9-clone group headed by StreamMgrSetChanGain_1d63f0 (64 B each).
   This member differs from the head in the worker called.  The reading is
   written up in StreamMgrSetChanGain_1d63f0.c. */

extern void StreamChanClose_1d6dc0(void *rec);

void StreamMgrCloseChan_1d67a0(void *base, s32 i)
{
    if (i < 0 || i >= 4) {
        return;
    }
    StreamChanClose_1d6dc0((u8 *)base + i * 224);
}
