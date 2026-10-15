#include "types.h"

extern s32 SaveSlotEntryIsBroken_3760f0(void *);

s32 SaveSlotEntryIsBrokenAt_373540(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsBroken_3760f0((u8 *)p + i * 2 + 0x78);
}
