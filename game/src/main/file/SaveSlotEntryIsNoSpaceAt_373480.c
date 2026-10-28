/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsNoSpaceAt_373480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 SaveSlotEntryIsNoSpaceAt_373480(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsNoSpace_376130((u8 *)p + i * 2 + 0x78);
}
