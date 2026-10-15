#include "types.h"

extern s32 SoundSlotGetLoadedId_1d2160(void *p);

s32 GameSceneSoundSlot1HasLoadedId_1d0810(void *a, s32 b)
{
    return SoundSlotGetLoadedId_1d2160((u8 *)a + 0xB138) == b;
}
