#include "types.h"
#include "event_vm.h"
#include "vm_slot.h"

extern void GameSceneSoundSlotsPoll_1d0a90(void *ctx, s32 v);
extern void GameSceneSoundEnvApplyPreset_1d0e30(void *ctx, s32 a, s32 b, s32 c);
extern void GameSceneSoundSetPollHold_1d1180(void *ctx, s32 v);
extern s32 ScriptGetInt_2490f0(Slot *v);

s32 EvCmdSoundEnvSet_244480(Slot *arg0, s32 arg1)
{
    if ((arg1 != 0) && (arg1 != 1)) {
        return 0;
    }
    GameSceneSoundSetPollHold_1d1180(gEventContext->arg, 0);
    if (arg1 == 1) {
        GameSceneSoundEnvApplyPreset_1d0e30(gEventContext->arg, ScriptGetInt_2490f0(arg0), 1, 0);
    }
    GameSceneSoundSlotsPoll_1d0a90(gEventContext->arg, 0);
    return 1;
}
