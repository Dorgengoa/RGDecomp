/* rgp:protos */
#define RGP_SELF_AiMoveToTargetPoint_2c0560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void AiMoveToTargetPoint_2c0560(s32 p0, s32 p1)
{
    u128 v30;

    AiGetTargetPoint_2c0fe0(p0, &v30);
    AiRouteMoveToPosMaybe_2beed0(p0, p1, &v30, 0);
}
