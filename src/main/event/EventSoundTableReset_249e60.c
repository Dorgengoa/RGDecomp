#include "types.h"

/* Sweeps all 0x40 slots. The receiver is parked in $17 rather than $4 because
   the loop counter has to occupy $5 on every call. */

extern void EventSoundEntryReset_24a0f0(void *self, s32 slot);

void EventSoundTableReset_249e60(void *self)
{
    s32 i;

    for (i = 0; i < 0x40; i++) {
        EventSoundEntryReset_24a0f0(self, i);
    }
}
