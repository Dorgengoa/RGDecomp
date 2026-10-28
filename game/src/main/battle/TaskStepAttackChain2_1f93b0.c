/* rgp:protos */
#define RGP_SELF_TaskStepAttackChain2_1f93b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004B86C0[];

/*rgp*/

s32 TaskStepAttackChain2_1f93b0(void)
{
    return (AttackChainStep_382270(D_004B86C0), (s32)0);
}
