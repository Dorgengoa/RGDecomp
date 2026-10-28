/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlotsPoll_1d0a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void GameSceneSoundSlotsPoll_1d0a90(void *arg0, s32 arg1) {
    u8 *addr;
    s32 i;

    if (GameSceneSoundPollIsHeld_1d1190((void *)arg0) == 0) {
        addr = (u8 *)arg0 + 0xB0B0;
        i = 0;
        do {
            if ((SoundSlotPoll_1d1c70(addr, arg1) != 0) && (i == 4)) {
                GameSceneEmitterSoundsReset_1d01d0(arg0);
            }
            i += 1;
            addr += 0x88;
        } while (i < 7);
    }
}
