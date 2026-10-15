#include "types.h"

extern s32 SaveSlotEntryIsValid_376050(void *);

s32 SaveSlotEntryIsValidAt_373440(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsValid_376050((u8 *)p + i * 2 + 0x78);
}
