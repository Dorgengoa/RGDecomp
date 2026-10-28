/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsBadDataAt_373500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 SaveSlotEntryIsBadDataAt_373500(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsBadData_376090((u8 *)p + i * 2 + 0x78);
}
