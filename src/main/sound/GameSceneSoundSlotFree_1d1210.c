#include "types.h"

extern void SoundSlotFree_1d21e0(u8 *p);

void GameSceneSoundSlotFree_1d1210(u8 *base, s8 i)
{
    if (i < 0 || i >= 7) return;
    SoundSlotFree_1d21e0(base + i * 136 + 0xB0B0);
}
