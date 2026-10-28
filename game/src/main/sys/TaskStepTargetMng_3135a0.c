/* rgp:protos */
#define RGP_SELF_TaskStepTargetMng_3135a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E7E60[];

/*rgp*/

s32 TaskStepTargetMng_3135a0(void)
{
    return (TargetMngStep_31f330(D_004E7E60), (s32)0);
}
