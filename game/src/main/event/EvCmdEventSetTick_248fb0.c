/* rgp:protos */
#define RGP_SELF_EvCmdEventSetTick_248fb0 1
#include "port/game_protos.h"
#line 1
#include "event_vm.h"

/* Event command 0x01: write the event player's tick counter. */

/*rgp*/

s32 EvCmdEventSetTick_248fb0(void *vm)
{
    EventPlayer *player = gEventContext->player;

    player->tick = ScriptGetInt_2490f0(vm);
    return 1;
}
