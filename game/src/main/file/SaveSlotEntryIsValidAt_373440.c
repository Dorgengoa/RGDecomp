/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsValidAt_373440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 SaveSlotEntryIsValidAt_373440(void *p, s32 i)
{
    if (i < 0 || i >= 0x32) return 0;
    return SaveSlotEntryIsValid_376050((u8 *)p + i * 2 + 0x78);
}
