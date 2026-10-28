/* rgp:protos */
#define RGP_SELF_EvCmdEventGetTick_248fe0 1
#include "port/game_protos.h"
#line 1
#include "event_vm.h"

/* Event command 0x00: read the event player's tick counter. */

/*rgp*/

s32 EvCmdEventGetTick_248fe0(void *vm)
{
    ScriptSetRefInt_249030(vm, gEventContext->player->tick);
    return 1;
}
