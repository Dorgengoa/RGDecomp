#include "types.h"
extern s32 SoundSlotGetBankId_1d2130(void *);
extern void SoundBankRelease_1bb6e0(s32);
extern void MemStackReset_14d830(void *);
extern void SoundSlotReleaseLoadHandle_1d1d60(void *);
void SoundSlotFree_1d21e0(u8 *p0)
{
    SoundBankRelease_1bb6e0(SoundSlotGetBankId_1d2130(p0));
    MemStackReset_14d830(p0 + 0x30);
    SoundSlotReleaseLoadHandle_1d1d60(p0);
    *(s32 *)(p0 + 0x10) = -1;
    *(s32 *)(p0 + 0x18) = -1;
}
