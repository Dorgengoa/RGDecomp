#include "event_vm.h"

/* Event command 0x00: read the event player's tick counter. */

extern void ScriptSetRefInt_249030(void *vm, s32 value);

s32 EvCmdEventGetTick_248fe0(void *vm)
{
    ScriptSetRefInt_249030(vm, gEventContext->player->tick);
    return 1;
}
