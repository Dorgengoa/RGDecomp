#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern void StreamSetChanVolume_1cd9b0(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventVoiceStop_24e820(s32 p0, s32 p1, f32 fa0)
{
    s32 r0;

    r0 = GetLoaderMgr_1f59d0();
    StreamSetChanVolume_1cd9b0(r0, p1, fa0);
}
