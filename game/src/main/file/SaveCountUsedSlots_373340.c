/* rgp:protos */
#define RGP_SELF_SaveCountUsedSlots_373340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

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
