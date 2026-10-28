/* rgp:protos */
#define RGP_SELF_TaskStepHeadNpc_3127c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E72B0[];

/*rgp*/

s32 TaskStepHeadNpc_3127c0(void)
{
    return (StepHeadNpcTask_2fad80(D_004E72B0), (s32)0);
}
