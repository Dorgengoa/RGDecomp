/* rgp:protos */
#define RGP_SELF_SoundSlotFree_1d21e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void SoundSlotFree_1d21e0(u8 *p0)
{
    SoundBankRelease_1bb6e0(SoundSlotGetBankId_1d2130(p0));
    MemStackReset_14d830(p0 + 0x30);
    SoundSlotReleaseLoadHandle_1d1d60(p0);
    *(s32 *)(p0 + 0x10) = -1;
    *(s32 *)(p0 + 0x18) = -1;
}
