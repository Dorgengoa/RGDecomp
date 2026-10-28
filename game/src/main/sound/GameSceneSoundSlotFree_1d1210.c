/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlotFree_1d1210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void GameSceneSoundSlotFree_1d1210(u8 *base, s8 i)
{
    if (i < 0 || i >= 7) return;
    SoundSlotFree_1d21e0(base + i * 136 + 0xB0B0);
}
