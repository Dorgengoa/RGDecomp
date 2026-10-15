#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004B86C0[];

extern s32 AttackChainDraw_380660(void *);

s32 TaskDrawAttackChain2_1f93a0(void)
{
    return AttackChainDraw_380660(D_004B86C0);
}
