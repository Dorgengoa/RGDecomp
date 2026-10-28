/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot6PlaySeVol_1d05c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

/*rgp*/

s32 GameSceneSoundSlot6PlaySeVol_1d05c0(void *p4, int rgp_a1, float rgp_f0)
{
    return (SoundSlotPlaySeVol_1d1ab0((u8 *)p4 + 0xB3E0, (int)rgp_a1, (float)rgp_f0), (s32)0);
}
