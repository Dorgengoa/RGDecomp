/* rgp:protos */
#define RGP_SELF_EvCmdCastSetEnabledMaybe_247e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "event_vm.h"
#include "vm_slot.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCastSetEnabledMaybe_247e60(Slot *args)
{
    void *arg;
    s32 want;
    s32 id;
    void *list;

    arg = gEventContext->arg;
    list = gEventContext->player->sub60;
    id = ScriptGetCodeAddr_249050(args++);
    want = EventCastFindKeyByName_24bb50(list, id);
    EventCastSetEnabledMaybe_24aa40(list, want, ScriptGetInt_2490f0(args), arg);
    return 1;
}
