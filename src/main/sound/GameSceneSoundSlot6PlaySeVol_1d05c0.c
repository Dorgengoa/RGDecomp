#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern s32 SoundSlotPlaySeVol_1d1ab0(void *);

s32 GameSceneSoundSlot6PlaySeVol_1d05c0(void *p4)
{
    return SoundSlotPlaySeVol_1d1ab0((u8 *)p4 + 0xB3E0);
}
