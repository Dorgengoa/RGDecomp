/* rgp:protos */
#define RGP_SELF_EffectMgrShutdown_2e3140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EffectMgrShutdown_2e3140(s32 p0)
{
    EffectMgrReleaseAll_2e2af0(p0);
    EffTableRelease_1a0fd0((p0 + 0x58));
}
