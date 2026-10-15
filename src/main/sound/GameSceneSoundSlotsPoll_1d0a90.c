#include "types.h"

extern void GameSceneEmitterSoundsReset_1d01d0(void *);
extern s32 GameSceneSoundPollIsHeld_1d1190(void);
extern s32 SoundSlotPoll_1d1c70(void *, s32);

void GameSceneSoundSlotsPoll_1d0a90(void *arg0, s32 arg1) {
    u8 *addr;
    s32 i;

    if (GameSceneSoundPollIsHeld_1d1190() == 0) {
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
