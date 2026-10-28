/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot5HasLoadedId_1d07d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 GameSceneSoundSlot5HasLoadedId_1d07d0(void *a, s32 b)
{
    return SoundSlotGetLoadedId_1d2160((u8 *)a + 0xB358) == b;
}
