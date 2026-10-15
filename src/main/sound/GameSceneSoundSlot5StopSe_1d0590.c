#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern s32 SoundSlotStopSe_1d1a10(void *);

s32 GameSceneSoundSlot5StopSe_1d0590(void *p4)
{
    return SoundSlotStopSe_1d1a10((u8 *)p4 + 0xB358);
}
