#include "types.h"

/* Queue an entry point on the event player. One is already queued unless
   +0x54 is negative, and a queued one is only displaced when the caller
   insists; otherwise this refuses with -1. */

typedef struct EventPlayer {
    u8 pad00[0x54];
    s32 queuedEntry;   /* +0x54, -1 = idle */
} EventPlayer;

s32 EventPlayerQueueEntry_250bd0(EventPlayer *this, s32 entry, s32 force)
{
    if (this->queuedEntry >= 0 && force == 0) {
        return -1;
    }
    this->queuedEntry = entry;
    return entry;
}
