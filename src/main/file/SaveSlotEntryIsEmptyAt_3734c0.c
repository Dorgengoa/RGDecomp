#include "types.h"

extern s32 SaveSlotEntryIsEmpty_376170(void *);

s32 SaveSlotEntryIsEmptyAt_3734c0(void *p, s32 i)
{
    if (i < 0 || 0x32 <= i) return 0;
    return SaveSlotEntryIsEmpty_376170((u8 *)p + i * 2 + 0x78);
}
