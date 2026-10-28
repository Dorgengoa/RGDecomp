/* rgp:protos */
#define RGP_SELF_TaskStepNpc_3127d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E72B0[];

/*rgp*/

s32 TaskStepNpc_3127d0(void)
{
    return (NpcObjTableStepMaybe_2fae50(D_004E72B0), (s32)0);
}
