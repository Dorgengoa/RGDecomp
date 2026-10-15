#include "types.h"

extern void EventCastRelease_24bf50(s32, s32, s32);
extern void EventVoiceListClear_24f4e0(s32);
extern void EventSoundTableStopAll_249eb0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventCleanupCastMesSound_249440(s32 p0, s32 p1)
{
    EventCastRelease_24bf50((p0 + 0x60), p1, -1);
    EventVoiceListClear_24f4e0((p0 + 0x420));
    EventSoundTableStopAll_249eb0((p0 + 0x4A0));
}
