#include "types.h"

extern s32 SaveSlotEntryIsNoSpace_376130(void *);

s32 SaveSlotEntryIsNoSpaceAt_373480(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsNoSpace_376130((u8 *)p + i * 2 + 0x78);
}
