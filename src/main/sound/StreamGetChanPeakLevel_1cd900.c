#include "types.h"

extern s32 GetStreamMgr_207ea0(void);
extern void StreamMgrChanGetPeakLevel_1d62b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void StreamGetChanPeakLevel_1cd900(s32 p0, s32 p1)
{
    s32 r0;

    r0 = GetStreamMgr_207ea0();
    StreamMgrChanGetPeakLevel_1d62b0(r0, p1);
}
