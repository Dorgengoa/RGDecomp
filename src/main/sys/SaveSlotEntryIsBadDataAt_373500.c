#include "types.h"

extern s32 SaveSlotEntryIsBadData_376090(void *);

s32 SaveSlotEntryIsBadDataAt_373500(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsBadData_376090((u8 *)p + i * 2 + 0x78);
}
