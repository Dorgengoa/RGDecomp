/* rgp:protos */
#define RGP_SELF_EffectResFindByName_2e2f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void * EffectResFindByName_2e2f10(s32 p0, s32 p1)
{
    s16 v1E;

    return EffectResFindByNameIdx_2e2e60(p0, p1, &v1E);
}
