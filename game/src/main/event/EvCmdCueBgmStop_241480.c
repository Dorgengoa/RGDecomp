/* rgp:protos */
#define RGP_SELF_EvCmdCueBgmStop_241480 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "event_vm.h"
#include "vm_slot.h"

/*rgp*/
/*rgp*/

s32 EvCmdCueBgmStop_241480(Slot *vm)
{
    s32 v4[4] __attribute__((aligned(16)));

    v4[1] = ScriptGetInt_2490f0(vm);
    v4[0] = 7;
    Vec4VectorPushBack_249120(gEventContext->player, &v4[0]);
    return 1;
}
