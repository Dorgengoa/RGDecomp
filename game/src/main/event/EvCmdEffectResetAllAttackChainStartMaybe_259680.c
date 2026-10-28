/* rgp:protos */
#define RGP_SELF_EvCmdEffectResetAllAttackChainStartMaybe_259680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdEffectResetAllAttackChainStartMaybe_259680(void)
{
    s32 r1;
    s32 r2;

    EffectResetAll_2d8900();
    r1 = ((s32)GetAttackChain_1fdb40());
    r2 = (AttackChainStartMaybe_382910(r1, 0, 6.0f), (s32)0);
    return 1;
}
