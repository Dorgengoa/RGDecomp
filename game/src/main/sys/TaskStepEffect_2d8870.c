/* rgp:protos */
#define RGP_SELF_TaskStepEffect_2d8870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004DCD50[];

/*rgp*/

s32 TaskStepEffect_2d8870(void)
{
    return (EffectMgrTick_2e3070(D_004DCD50), (s32)0);
}
