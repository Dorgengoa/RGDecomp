/* rgp:protos */
#define RGP_SELF_TaskDrawAttackChain2_1f93a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004B86C0[];

/*rgp*/

s32 TaskDrawAttackChain2_1f93a0(void)
{
    return (AttackChainDraw_380660(D_004B86C0), (s32)0);
}
