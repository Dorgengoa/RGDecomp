#include "types.h"

extern s32 SoundSlotGetLoadedId_1d2160(void *p);

s32 GameSceneSoundSlot5HasLoadedId_1d07d0(void *a, s32 b)
{
    return SoundSlotGetLoadedId_1d2160((u8 *)a + 0xB358) == b;
}
