/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsEmptyAt_3734c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 SaveSlotEntryIsEmptyAt_3734c0(void *p, s32 i)
{
    if (i < 0 || 0x32 <= i) return 0;
    return SaveSlotEntryIsEmpty_376170((u8 *)p + i * 2 + 0x78);
}
