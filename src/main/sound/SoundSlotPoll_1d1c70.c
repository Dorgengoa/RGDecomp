#include "types.h"

extern void PadWaitReady_1849e0(void *arg0);
extern void SoundBankRelease_1bb6e0(s32 arg0);
extern void LoadHandlePoll_1ccb00(void);
extern void SoundSlotStartLoaded_1d1ea0(void *arg0, s32 arg1);
extern s32 SoundSlotGetBankId_1d2130(void *arg0);
extern s32 SoundSlotGetLoadState_1d2170(void *arg0);
extern void SoundSlotFree_1d21e0(void *arg0);
extern u8 D_004B2570[0x100];

s32 SoundSlotPoll_1d1c70(void *arg0, s32 arg1)
{
    s32 r;

    if (*(s32 *)((u8 *)arg0 + 0xC) < 0) {
        return 0;
    }
    LoadHandlePoll_1ccb00();
    switch (SoundSlotGetLoadState_1d2170(arg0)) {
    case -1:
        SoundBankRelease_1bb6e0(SoundSlotGetBankId_1d2130(arg0));
        SoundSlotFree_1d21e0(arg0);
        return 1;
    case 1:
        SoundSlotStartLoaded_1d1ea0(arg0, *(s32 *)((u8 *)arg0 + 0x4));
        r = ~(*(s32 *)((u8 *)arg0 + 0x18)) != 0;
        if (arg1 != 0) {
            PadWaitReady_1849e0(D_004B2570);
        }
        return r;
    case 0:
        if (arg1 != 0) {
            PadWaitReady_1849e0(D_004B2570);
        }
        break;
    }
    return 0;
}
