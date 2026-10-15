#include "types.h"
#include "event_vm.h"
#include "vm_slot.h"

extern s32 ScriptGetInt_2490f0(Slot *v);
extern void Vec4VectorPushBack_249120(EventPlayer *player, void *src);

s32 EvCmdCueBgmStop_241480(Slot *vm)
{
    s32 v4[4];

    v4[1] = ScriptGetInt_2490f0(vm);
    v4[0] = 7;
    Vec4VectorPushBack_249120(gEventContext->player, &v4[0]);
    return 1;
}
