#include "types.h"
#include "event_vm.h"
#include "vm_slot.h"

extern s32 ScriptGetCodeAddr_249050(Slot *v);
extern s32 ScriptGetInt_2490f0(Slot *v);
extern void EventCastSetEnabledMaybe_24aa40(void *, s32, s32, void *);
extern s32 EventCastFindKeyByName_24bb50(void *, s32);

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
