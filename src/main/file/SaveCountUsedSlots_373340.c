#include "types.h"

extern s32 SaveSlotEntryIsValidAt_373440(s32 arg0, s32 arg1);
extern s32 SaveSlotEntryIsBadDataAt_373500(s32 arg0, s32 arg1);
extern s32 SaveSlotEntryIsBrokenAt_373540(s32 arg0, s32 arg1);

s32 SaveCountUsedSlots_373340(s32 arg0)
{
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < 0x32; i++) {
        if (SaveSlotEntryIsValidAt_373440(arg0, i) != 0 || SaveSlotEntryIsBrokenAt_373540(arg0, i) != 0 || SaveSlotEntryIsBadDataAt_373500(arg0, i) != 0) {
            count += 1;
        }
    }
    return count;
}
