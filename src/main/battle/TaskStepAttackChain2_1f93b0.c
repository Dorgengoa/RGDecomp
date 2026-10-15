#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004B86C0[];

extern s32 AttackChainStep_382270(void *);

s32 TaskStepAttackChain2_1f93b0(void)
{
    return AttackChainStep_382270(D_004B86C0);
}
