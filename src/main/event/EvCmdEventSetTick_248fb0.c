#include "event_vm.h"

/* Event command 0x01: write the event player's tick counter. */

extern s32 ScriptGetInt_2490f0(void *vm);

s32 EvCmdEventSetTick_248fb0(void *vm)
{
    EventPlayer *player = gEventContext->player;

    player->tick = ScriptGetInt_2490f0(vm);
    return 1;
}
