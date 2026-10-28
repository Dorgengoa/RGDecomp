/* rgp:protos */
#define RGP_SELF_EventSoundTableReset_249e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Sweeps all 0x40 slots. The receiver is parked in $17 rather than $4 because
   the loop counter has to occupy $5 on every call. */

/*rgp*/

void EventSoundTableReset_249e60(void *self)
{
    s32 i;

    for (i = 0; i < 0x40; i++) {
        EventSoundEntryReset_24a0f0(self, i);
    }
}
