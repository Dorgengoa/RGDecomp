/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot1HasLoadedId_1d0810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 GameSceneSoundSlot1HasLoadedId_1d0810(void *a, s32 b)
{
    return SoundSlotGetLoadedId_1d2160((u8 *)a + 0xB138) == b;
}
