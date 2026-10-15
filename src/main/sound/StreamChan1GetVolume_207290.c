#include "types.h"

extern s32 GetStreamMgr_207ea0(void);
extern void StreamMgrChanGetVolume_1d68c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void StreamChan1GetVolume_207290(void)
{
    s32 r0;

    r0 = GetStreamMgr_207ea0();
    StreamMgrChanGetVolume_1d68c0(r0, 1);
}
